using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Popups;
using Windows.Storage;
using System.Text.RegularExpressions;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace NotesApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class EditNote : Page
    {
        Note selectedNote;
        public EditNote()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.  The Parameter
        /// property is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            if (e.Parameter != null && e.Parameter is Note)
            {
                selectedNote = e.Parameter as Note;
                tboxNoteContent.DataContext = selectedNote;
                tboxNoteTitle.DataContext = selectedNote;
            }

        }

        private async void tboxNoteContent_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            PopupMenu pMenu = new PopupMenu();
            UICommand SelectAllCommand = new UICommand();
            SelectAllCommand.Label = "SelectAll";
            pMenu.Commands.Add(SelectAllCommand);
            var chosenCommand = await pMenu.ShowForSelectionAsync(new Rect(e.GetPosition(null), e.GetPosition(null)));
            if (chosenCommand != null)
            {
                tboxNoteContent.SelectAll();
            }
        }

        private void bttnCancel_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private void bttnSave_Click(object sender, RoutedEventArgs e)
        {
            ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
            ApplicationDataCompositeValue composite_old = new ApplicationDataCompositeValue();
            composite["Title"] = tboxNoteTitle.Text;
            composite["Content"] = tboxNoteContent.Text;
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            int lastIndex = Convert.ToInt32(localSettings.Values["NoteNum"].ToString());
            for (int i = 0; i < lastIndex; i++)
            {
                try
                {
                    if (localSettings.Values[i.ToString()] != null)
                    {
                        composite_old = localSettings.Values[i.ToString()] as ApplicationDataCompositeValue;
                        if (selectedNote.Title == composite_old["Title"] as string && selectedNote.Content == composite_old["Content"] as string)
                        {
                            localSettings.Values[i.ToString()] = composite;
                            break;
                        }
                    }
                }
                catch { }
            }
            Frame.Navigate(typeof(MainPage));
        }
    }
    }

