using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace filters
{
    public partial class Form1 : Form
    {
        Bitmap image, trueImage;

        public Form1()
        {
            InitializeComponent();
        }

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image files | *.png; *.jpg; *.bmp | All Files (*.*) | *.*";

            if (dialog.ShowDialog() == DialogResult.OK)
                image = new Bitmap(dialog.FileName);

            pictureBox1.Image = image;
            trueImage = image;
            pictureBox1.Refresh();
        }

        private void сохранитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                SaveFileDialog dialog = new SaveFileDialog();
                dialog.Title = "Сохранить";

                dialog.OverwritePrompt = true;
                dialog.CheckPathExists = true;

                dialog.Filter = "Image files | *.png, *.jpg; *.bmp | All Files (*.*) | *.*";

                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        image.Save(dialog.FileName, System.Drawing.Imaging.ImageFormat.Jpeg);
                    }
                    catch
                    {
                        MessageBox.Show("Невозможно сохранить изображение", "Ошибка",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }

        private void Отмена_Click(object sender, EventArgs e)
        {
            backgroundWorker1.CancelAsync();
        }

        private void сброситьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            image = trueImage;
            pictureBox1.Image = image;
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            Bitmap newImage = ((Filters)e.Argument).processImage(image, backgroundWorker1);
            if (backgroundWorker1.CancellationPending != true)
                image = newImage;
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBar1.Value = e.ProgressPercentage;
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!e.Cancelled)
            {
                pictureBox1.Image = image;
                pictureBox1.Refresh();
            }

            progressBar1.Value = 0;
        }

        /* ---------- Pointner ---------- */

        private void инверсияToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new InvertFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void чернобелыйToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new GrayScaleFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void сепияToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new SepiaFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void яркостьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new BrightnessFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void волныToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new WavesFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void стеклоToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new GlassFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void поворотToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new RoateFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        /* ---------- Matrix ---------- */

        private void размытиеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new BlurFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void гауссToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new GaussianFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void собельToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new SobelFilter(image);
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void резкостьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new SharpnessFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        /* ---------- Morfologe ---------- */

        private void сужениToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new ErosionFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void расширениеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new DilationFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void открытиеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new OpeningFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }

        private void закрытиеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Filters filter = new ClosingFilter();
                backgroundWorker1.RunWorkerAsync(filter);
            }
        }
    }
}
