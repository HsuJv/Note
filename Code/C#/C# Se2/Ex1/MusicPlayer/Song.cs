using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace MusicPlayer
{
    class Song
    {
        public string SongTitle { get; set; }
        public string SongThumbNailPath { get; set; }
        public BitmapImage SongThumbnail
        {
            get
            {
                if (string.IsNullOrEmpty(SongThumbNailPath))
                    return new BitmapImage();
                else
                    return (new BitmapImage(new Uri(SongThumbNailPath)));
            }
        }
        public string SongPath { get; set; }
        public Song(string title, string thumbnailImagePath, string songpath)
        {
            SongTitle = title;
            SongThumbNailPath = thumbnailImagePath;
            SongPath = songpath;
        }
    }
}
