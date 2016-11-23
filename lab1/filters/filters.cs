using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.ComponentModel;

namespace filters
{
    abstract class Filters
    {
        protected abstract Color calculateNewPixelColor(Bitmap sourceImage, int x, int y);

        public virtual Bitmap processImage(Bitmap sourceImage, BackgroundWorker worker)
        {
            Bitmap resultImage = new Bitmap(sourceImage.Width, sourceImage.Height);

            for (int i = 0; i < sourceImage.Width; i++)
            {
                worker.ReportProgress((int)((float)i / resultImage.Width * 100));

                if (worker.CancellationPending)
                    return null;

                for (int j = 0; j < sourceImage.Height; j++)
                    resultImage.SetPixel(i, j, calculateNewPixelColor(sourceImage, i, j));
             }

            return resultImage;
        }

        public int Clamp(int value, int min, int max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;
            return value;
        }
    }

    /* ---------- Pointner ---------- */

    class InvertFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);
            Color resultColor = Color.FromArgb(255 - sourceColor.R, 255 - sourceColor.G, 255 - sourceColor.B);

            return resultColor;
        }
    }

    class GrayScaleFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);

            byte intensity = (byte)(0.36 * sourceColor.R + 0.53 * sourceColor.G + 0.11 * sourceColor.B);
            Color resultColor = Color.FromArgb(intensity, intensity, intensity);

            return resultColor;
        }
    }

    class SepiaFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);
            float K = 20;
            int intensity = (int)(0.36 * sourceColor.R + 0.53 * sourceColor.G + 0.11 * sourceColor.B);

            float R = (intensity + (2 * K));
            float G = (float)(intensity + (0.5 * K));
            float B = (intensity - (1 * K));

            return Color.FromArgb(
                Clamp((int)R, 0, 255),
                Clamp((int)G, 0, 255),
                Clamp((int)B, 0, 255)
                );
        }
    }

    class BrightnessFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);
            float K = 25;

            float R = sourceColor.R + K;
            float G = sourceColor.G + K;
            float B = sourceColor.B + K;

            return Color.FromArgb(
                Clamp((int)R, 0, 255),
                Clamp((int)G, 0, 255),
                Clamp((int)B, 0, 255)
                );
        }
    }

    class WavesFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {           
            int newX = Clamp((int)(x + (20 * Math.Sin(2 * Math.PI * y / 60))), 0, sourceImage.Width - 1);
            int newY = y;

            return sourceImage.GetPixel(newX, newY);
        }
    }

    class GlassFilter : Filters
    {
        Random rnd = new Random();

        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            int newX = Clamp((int)(x + (rnd.NextDouble() - 0.5) * 10), 0, sourceImage.Width - 1);
            int newY = Clamp((int)(y + (rnd.NextDouble() - 0.5) * 10), 0, sourceImage.Height - 1);

            return sourceImage.GetPixel(newX, newY);
        }
    }

    class RoateFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            int x0 = sourceImage.Width / 2;
            int y0 = sourceImage.Height / 2;
            double center = Math.PI / 2;

            int newX = Clamp((int)((x - x0) * Math.Cos(center) - (y - y0)
                        * Math.Sin(center) + x0), 0, sourceImage.Width - 1);
            int newY = Clamp((int)((x - x0) * Math.Sin(center) - (y - y0)
                        * Math.Cos(center) + y0), 0, sourceImage.Height - 1);

            return sourceImage.GetPixel(newX, newY);
        }
    }

    /* ---------- Matrix ---------- */

    class MatrixFilter : Filters
    {
        protected float[,] kernel = null;
        protected MatrixFilter() { }

        public MatrixFilter(float[,] kernel)
        {
            this.kernel = kernel;
        }

        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            int radiusX = kernel.GetLength(0) / 2;
            int radiusY = kernel.GetLength(1) / 2;

            float resultR = 0;
            float resultG = 0;
            float resultB = 0;

            for (int l = -radiusY; l <= radiusY; l++)
                for (int k = -radiusX; k <= radiusX; k++)
                {
                    int idX = Clamp(x + k, 0, sourceImage.Width - 1);
                    int idY = Clamp(y + l, 0, sourceImage.Height - 1);

                    Color neighborColor = sourceImage.GetPixel(idX, idY);
                    resultR += neighborColor.R * kernel[k + radiusX, l + radiusY];
                    resultG += neighborColor.G * kernel[k + radiusX, l + radiusY];
                    resultB += neighborColor.B * kernel[k + radiusX, l + radiusY];
                }

            return Color.FromArgb(
                Clamp((int)resultR, 0, 255),
                Clamp((int)resultG, 0, 255),
                Clamp((int)resultB, 0, 255));
        }
    }

    class BlurFilter : MatrixFilter
    {
        public BlurFilter()
        {
            int sizeX = 3;
            int sizeY = 3;
            kernel = new float[sizeX, sizeY];
            for (int i = 0; i < sizeX; i++)
                for (int j = 0; j < sizeY; j++)
                    kernel[i, j] = 1.0f / (float)(sizeX * sizeY);
        }
    }

    class GaussianFilter : MatrixFilter
    {
        public void createGaussianKernel(int radius, float sigma)
        {
            int size = 2 * radius + 1;
            kernel = new float[size, size]; 
            float norm = 0;

            for (int i = -radius; i <= radius; i++)
                for (int j = -radius; j <= radius; j++)
                {
                    kernel[i + radius, j + radius] = (float)(Math.Exp(-(i * i + j * j) / (sigma * sigma)));
                    norm += kernel[i + radius, j + radius];
                }

            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    kernel[i, j] /= norm;
        }

        public GaussianFilter()
        {
            createGaussianKernel(3, 2);
        }
    }

    class SobelFilter : Filters
    {
        Bitmap picture;
        float[,] kernelX, kernelY;

        public SobelFilter(Bitmap soursePic)
        {            
            kernelX = new float[3, 3] { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
            kernelY = new float[3, 3] { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };

            picture = soursePic;
        }

        private Color applyKernel (float[,] kernel, int x, int y)
        {
            int radiusX = kernel.GetLength(0) / 2;
            int radiusY = kernel.GetLength(1) / 2;

            float resultR = 0;
            float resultG = 0;
            float resultB = 0;

            for (int l = -radiusY; l <= radiusY; l++)
                for (int k = -radiusX; k <= radiusX; k++)
                {
                    int idX = Clamp(x + k, 0, picture.Width - 1);
                    int idY = Clamp(y + l, 0, picture.Height - 1);

                    Color neighborColor = picture.GetPixel(idX, idY);
                    resultR += neighborColor.R * kernel[k + radiusX, l + radiusY];
                    resultG += neighborColor.G * kernel[k + radiusX, l + radiusY];
                    resultB += neighborColor.B * kernel[k + radiusX, l + radiusY];
                }

            return Color.FromArgb(
                Clamp((int)resultR, 0, 255),
                Clamp((int)resultG, 0, 255),
                Clamp((int)resultB, 0, 255));
        }

        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            float resultR, resultG, resultB;
            Color pixelX, pixelY;

            pixelX = applyKernel(kernelX, x, y);
            pixelY = applyKernel(kernelY, x, y);
            
            resultR = (float)Math.Sqrt(Math.Pow(pixelX.R, 2) + Math.Pow(pixelY.R, 2));
            resultG = (float)Math.Sqrt(Math.Pow(pixelX.G, 2) + Math.Pow(pixelY.G, 2));
            resultB = (float)Math.Sqrt(Math.Pow(pixelX.B, 2) + Math.Pow(pixelY.B, 2));

            return Color.FromArgb(
                        Clamp((int)resultR, 0, 255),
                        Clamp((int)resultG, 0, 255),
                        Clamp((int)resultB, 0, 255)
                        );
        }
    }

    class SharpnessFilter : MatrixFilter
    {
        public SharpnessFilter()
        {
            const int sizeX = 3;
            const int sizeY = 3;
            kernel = new float[sizeX, sizeY] { { 0, -1, 0 }, { -1, 5, -1 }, { 0, -1, 0 } };
        }
    }

    /* ---------- Morfologe ---------- */

    abstract class MorfologeFilter : Filters
    {
        protected int MW = 3, MH = 3;
        protected int[,] Mask = { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } };

        public override Bitmap processImage(Bitmap sourceImage, BackgroundWorker worker)
        {
            Bitmap resultImage = new Bitmap(sourceImage.Width, sourceImage.Height);

            for (int i = MW / 2; i < sourceImage.Width - MW / 2; i++)
            {
                worker.ReportProgress((int)((float)i / resultImage.Width * 100));
                if (worker.CancellationPending)
                    return null;

                for (int j = MH / 2; j < sourceImage.Height - MH / 2; j++)
                    resultImage.SetPixel(i, j, calculateNewPixelColor(sourceImage, i, j));                
            }

            return resultImage;
        }
    }

    class ErosionFilter : MorfologeFilter
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {         
            Color min = Color.FromArgb(255, 255, 255);

            for (int j = -MH / 2; j <= MH / 2; j++)
                for (int i = -MW / 2; i <= MW / 2; i++)
                {
                    Color pixel = sourceImage.GetPixel(x + i, y + j);

                    if (Mask[i + MW / 2, j + MH / 2] != 0 && pixel.R < min.R && pixel.G < min.G && pixel.B < min.B)                    
                        min = pixel;                    
                }

            return min;
        }
    }

    class DilationFilter : MorfologeFilter
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color max = Color.FromArgb(0, 0, 0);

            for (int j = -MH / 2; j <= MH / 2; j++)
                for (int i = -MW / 2; i <= MW / 2; i++)
                {
                    Color pixel = sourceImage.GetPixel(x + i, y + j);

                    if (Mask[i + MW / 2, j + MH / 2] == 1 && pixel.R > max.R && pixel.G > max.G && pixel.B > max.B)
                        max = pixel;
                }

            return max;
        }
    }

    class OpeningFilter : MorfologeFilter
    {
        public override Bitmap processImage(Bitmap sourceImage, BackgroundWorker worker)
        {
            Bitmap erosion = new Bitmap(sourceImage.Width, sourceImage.Height);

            for (int i = MW / 2; i < erosion.Width - MW / 2; i++)
            {
                worker.ReportProgress((int)((float)i / erosion.Width * 50));
                if (worker.CancellationPending)
                    return null;

                for (int j = MH / 2; j < erosion.Height - MH / 2; j++)
                    erosion.SetPixel(i, j, calculateNewPixelColor(sourceImage, i, j));
            }

            Bitmap result = new Bitmap(erosion);

            for (int i = MW / 2; i < result.Width - MW / 2; i++)
            {
                worker.ReportProgress((int)((float)i / result.Width * 50 + 50));
                if (worker.CancellationPending)
                    return null;

                for (int j = MH / 2; j < result.Height - MH / 2; j++)
                    result.SetPixel(i, j, calcDilation(erosion, i, j));
            }

            return result;
        }

        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color min = Color.FromArgb(255, 255, 255);

            for (int j = -MH / 2; j <= MH / 2; j++)
                for (int i = -MW / 2; i <= MW / 2; i++)
                {
                    Color pixel = sourceImage.GetPixel(x + i, y + j);

                    if (Mask[i + MW / 2, j + MH / 2] != 0 && pixel.R < min.R && pixel.G < min.G && pixel.B < min.B)
                        min = pixel;
                }

            return min;
        }

        private Color calcDilation(Bitmap sourceImage, int x, int y)
        {
            Color max = Color.FromArgb(0, 0, 0);

            for (int j = -MH / 2; j <= MH / 2; j++)
                for (int i = -MW / 2; i <= MW / 2; i++)
                {
                    Color pixel = sourceImage.GetPixel(x + i, y + j);

                    if (Mask[i + MW / 2, j + MH / 2] == 1 && pixel.R > max.R && pixel.G > max.G && pixel.B > max.B)
                        max = pixel;
                }

            return max;
        }
    }

    class ClosingFilter : MorfologeFilter
    {
        public override Bitmap processImage(Bitmap sourceImage, BackgroundWorker worker)
        {
            Bitmap dilation = new Bitmap(sourceImage.Width, sourceImage.Height);

            for (int i = MW / 2; i < dilation.Width - MW / 2; i++)
            {
                worker.ReportProgress((int)((float)i / dilation.Width * 50));
                if (worker.CancellationPending)
                    return null;

                for (int j = MH / 2; j < dilation.Height - MH / 2; j++)
                    dilation.SetPixel(i, j, calculateNewPixelColor(sourceImage, i, j));
            }

            Bitmap result = new Bitmap(dilation);

            for (int i = MW / 2; i < result.Width - MW / 2; i++)
            {
                worker.ReportProgress((int)((float)i / result.Width * 50 + 50));
                if (worker.CancellationPending)
                    return null;

                for (int j = MH / 2; j < result.Height - MH / 2; j++)
                    result.SetPixel(i, j, calcErosion(dilation, i, j));
            }

            return result;
        }

        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {

            Color max = Color.FromArgb(0, 0, 0);

            for (int j = -MH / 2; j <= MH / 2; j++)
                for (int i = -MW / 2; i <= MW / 2; i++)
                {
                    Color pixel = sourceImage.GetPixel(x + i, y + j);

                    if (Mask[i + MW / 2, j + MH / 2] == 1 && pixel.R > max.R && pixel.G > max.G && pixel.B > max.B)
                        max = pixel;
                }

            return max;
        }

        private Color calcErosion(Bitmap sourceImage, int x, int y)
        {
            Color min = Color.FromArgb(255, 255, 255);

            for (int j = -MH / 2; j <= MH / 2; j++)
                for (int i = -MW / 2; i <= MW / 2; i++)
                {
                    Color pixel = sourceImage.GetPixel(x + i, y + j);

                    if (Mask[i + MW / 2, j + MH / 2] != 0 && pixel.R < min.R && pixel.G < min.G && pixel.B < min.B)
                        min = pixel;
                }

            return min;
        }
    }
}
