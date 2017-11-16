using System;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace MusicPlayer
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        bool isPlaying = false;
        TextBlock txtPlayStatus = new TextBlock();
        List<Song> playList = new List<Song>();
        Song currentSong = null;
        int currentSongIndex;
        public MainPage()
        {
            this.InitializeComponent();
            txtPlayStatus.Name = "txtPlayStatus";
            txtPlayStatus.Margin = new Thickness(390, 535, 25, 198);
            txtPlayStatus.FontSize = 18;
            txtPlayStatus.TextAlignment = TextAlignment.Center;
            grdMusicPlayer.Children.Add(txtPlayStatus);
        }
        private void addSongsToPlayList()
        {
            playList.Add(new Song("Flo Rida Whistle", "ms-appx:///MediaCollections/Thumbnails/NoThumbnail.PNG", "ms-appx:///MediaCollections/Music/Flo_Rida_-_Whistle.mp3"));
            playList.Add(new Song("Katy", "ms-appx:///MediaCollections/Thumbnails/NoThumbnail.PNG", "ms-appx:///MediaCollections/Music/Katy.mp3"));
        }
        void loadPlayList()
        {
            foreach (Song s in playList)
                lstViewPlaylist.Items.Add(" " + s.SongTitle);
        }
        void loadSelectedSong(string songToSelect)
        {
            foreach (Song s in playList)
                if (s.SongTitle == songToSelect.Trim())
                    currentSong = s;
            mediaSource.PosterSource = currentSong.SongThumbnail;
            mediaSource.Source = new Uri(currentSong.SongPath);
        }
        private void lstViewPlaylist_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            currentSongIndex = lstViewPlaylist.SelectedIndex;
            loadSelectedSong(lstViewPlaylist.SelectedItem as string);
            mediaSource.Stop();
            bttnPlay.Visibility = Windows.UI.Xaml.Visibility.Visible;
            bttnPause.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            addSongsToPlayList();
            loadPlayList();
            sldrVolume.Value = sldrVolume.Maximum;
            prgsBarSongPosition.Value = 0.0;
            prgsBarSongPosition.ValueChanged += prgsBarSongPosition_ValueChanged;
            lstViewPlaylist.SelectedIndex = 0;
        }
        void prgsBarSongPosition_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            if (Math.Abs(e.NewValue - e.OldValue) > 100)
                mediaSource.Position = new TimeSpan(0, 0, 0, 0, Convert.ToInt32(prgsBarSongPosition.Value));
            txtPlayStatus.Text = mediaSource.Position.Hours + " : " + mediaSource.Position.Minutes + " : " + mediaSource.Position.Seconds + " / " +
                mediaSource.NaturalDuration.TimeSpan.Hours + " : " + mediaSource.NaturalDuration.TimeSpan.Minutes + " : " + mediaSource.NaturalDuration.TimeSpan.Seconds;
        }
        void playSong()
        {
            prgsBarSongPosition.Minimum = 0.0;
            prgsBarSongPosition.Maximum = mediaSource.NaturalDuration.TimeSpan.TotalMilliseconds;
            bttnPause.Visibility = Windows.UI.Xaml.Visibility.Visible;
            bttnPlay.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
            mediaSource.Play();
            isPlaying = true;
            displayProgress();
        }
        async void displayProgress()
        {
            await Task.Delay(1000);
            prgsBarSongPosition.Value = mediaSource.Position.TotalMilliseconds;
            if (isPlaying)
            {
                if (mediaSource.Position.TotalMilliseconds < mediaSource.NaturalDuration.TimeSpan.TotalMilliseconds)
                    displayProgress();
                else
                {
                    if (!mediaSource.IsLooping)
                    {
                        isPlaying = false;
                        bttnPause.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
                        bttnPlay.Visibility = Windows.UI.Xaml.Visibility.Visible;
                    }
                    else
                        displayProgress();
                }
            }
        }
        private void bttnPlay_Click(object sender, RoutedEventArgs e)
        {
            playSong();
        }
        void pauseSong()
        {
            bttnPause.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
            bttnPlay.Visibility = Windows.UI.Xaml.Visibility.Visible;
            mediaSource.Pause();
            isPlaying = false;
        }
        private void bttnPause_Click(object sender, RoutedEventArgs e)
        {
            pauseSong();
        }
        private void bttnNext_Click(object sender, RoutedEventArgs e)
        {
            if (currentSongIndex < playList.Count - 1)
                currentSongIndex++;
            if (isPlaying)
                mediaSource.Stop();
            lstViewPlaylist.SelectedIndex = currentSongIndex;
        }
        private void bttnPrevious_Click(object sender, RoutedEventArgs e)
        {
            if (currentSongIndex > 0)
                currentSongIndex--;
            if (isPlaying)
                mediaSource.Stop();
            lstViewPlaylist.SelectedIndex = currentSongIndex;
        }
        private void sldrVolume_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            mediaSource.Volume = sldrVolume.Value / 100;
        }
        private void tglSwtchMediaRepeat_Toggled(object sender, RoutedEventArgs e)
        {
            mediaSource.IsLooping = tglSwitchMediaRepeat.IsOn;
        }
    }
}

