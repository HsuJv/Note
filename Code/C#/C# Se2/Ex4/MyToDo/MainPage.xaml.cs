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
using System.Collections.ObjectModel;
using Windows.Storage.Pickers;
using Windows.Storage;
using Windows.UI.ViewManagement;
using Windows.UI.Popups;
using Windows.Storage.Streams;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace MyToDo
{
    public class ToDos
    {
        public string TaskDescription { get; set; }
        public string TaskCategory { get; set; }
        public string TaskDeadLine { get; set; }
        public bool isCompleted { get; set; }
        public ToDos(string description, string category, string deadline, bool isCompleted = false)
        {
            TaskDescription = description;
            TaskCategory = category;
            TaskDeadLine = deadline;
            this.isCompleted = isCompleted;
        }
    }
    public sealed partial class MainPage : Page
    {


        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.  The Parameter
        /// property is typically used to configure the page.</param>
        ObservableCollection<ToDos> toDosCollection = new ObservableCollection<ToDos>();

        public MainPage()
        {
            this.InitializeComponent();
            fillYear(2012, 2090);
            fillMonth();
            fillDays();
            cboxMonth.SelectionChanged += cboxMonth_SelectionChanged;
            cboxYear.SelectionChanged += cboxYear_SelectionChanged;
            lstViewTaskCategories.Items.Add("Personal");
            lstViewTaskCategories.Items.Add("Official");
            lstViewTaskCategories.SelectedIndex = 0;

        }

        void cboxYear_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            fillDays();
        }

        void cboxMonth_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            fillDays();
        }

        void fillDays()
        {
            cboxDay.Items.Clear();
            cboxDay.Items.Add("");
            try
            {
                int days = DateTime.DaysInMonth(Convert.ToInt32(cboxYear.SelectedValue), getMonth(cboxMonth.SelectedValue.ToString()));
                for (int i = 1; i <= days; i++)
                    cboxDay.Items.Add(i);
                cboxDay.SelectedIndex = 0;
            }
            catch (Exception ex)
            {


            }

        }

        int getMonth(string monthName)
        {
            switch (monthName)
            {
                case "January":
                    return 1;
                case "February":
                    return 2;
                case "March":
                    return 3;
                case "April":
                    return 4;
                case "May":
                    return 5;
                case "June":
                    return 6;
                case "July":
                    return 7;
                case "August":
                    return 8;
                case "September":
                    return 9;
                case "October":
                    return 10;
                case "November":
                    return 11;
                case "December":
                    return 12;
                default:
                    return -1;

            }
        }

        void fillMonth()
        {
            cboxMonth.Items.Add("");
            cboxMonth.Items.Add("January");
            cboxMonth.Items.Add("February");
            cboxMonth.Items.Add("March");
            cboxMonth.Items.Add("April");
            cboxMonth.Items.Add("May");
            cboxMonth.Items.Add("June");
            cboxMonth.Items.Add("July");
            cboxMonth.Items.Add("August");
            cboxMonth.Items.Add("September");
            cboxMonth.Items.Add("October");
            cboxMonth.Items.Add("November");
            cboxMonth.Items.Add("December");
            cboxMonth.SelectedIndex = 0;
        }

        void fillYear(int startYear, int endYear)
        {
            cboxYear.Items.Add("");
            for (int i = startYear; i <= endYear; i++)
                cboxYear.Items.Add(i);
            cboxYear.SelectedIndex = 0;
        }

        private void bttnAddToDo_Click_1(object sender, RoutedEventArgs e)
        {
            txtdesc.Text = "Please provide complete information.";

            if (string.IsNullOrEmpty(txtTaskDescription.Text.Trim()) || cboxYear.SelectedIndex == 0 || cboxMonth.SelectedIndex == 0 || cboxDay.SelectedIndex == 0)
            {
                txtdesc.Visibility = Windows.UI.Xaml.Visibility.Visible;

                return;
            }
            else
            {
                txtdesc.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
                toDosCollection.Add(new ToDos(txtTaskDescription.Text, lstViewTaskCategories.SelectedValue.ToString(), cboxMonth.SelectedValue.ToString() + " " + cboxDay.SelectedValue.ToString() + ", " + cboxYear.SelectedValue.ToString()));
                grdToDos.ItemsSource = toDosCollection;
                txtTaskDescription.Text = "";
                cboxDay.SelectedIndex = cboxMonth.SelectedIndex = cboxYear.SelectedIndex = 0;
                txtTaskDescription.Focus(Windows.UI.Xaml.FocusState.Programmatic);
            }

        }

        private void bttnRemoveFromGrid_Click_1(object sender, RoutedEventArgs e)
        {
            if (grdToDos.SelectedItems.Count > 0)
            {
                try
                {
                    if (toDosCollection.Count > 1)
                    {
                        toDosCollection.Remove(grdToDos.SelectedItem as ToDos);
                        grdToDos.ItemsSource = toDosCollection;
                    }
                    else
                    {
                        toDosCollection.Clear();
                        grdToDos.ItemsSource = null;
                    }
                }
                catch (Exception)
                {


                }

            }


        }

        private void grdToDos_SelectionChanged_1(object sender, SelectionChangedEventArgs e)
        {
            if (grdToDos.Items.Count > 0 && grdToDos.SelectedItems.Count > 0)
                bttnRemoveToDo.Visibility = Windows.UI.Xaml.Visibility.Visible;
            else
                bttnRemoveToDo.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
        }

        bool unSnapped = true;

        async void EnsureUnsnapped()
        {
            // FilePicker APIs will not work if the application is in 
            //a snapped state
            // If an app wants to show a FilePicker while snapped, it
            //must attempt to unsnap first
            unSnapped = ((ApplicationView.Value != ApplicationViewState.Snapped) || ApplicationView.TryUnsnap());
            if (!unSnapped)
            {
                MessageDialog msg = new MessageDialog("Cannot open file picker in snapped view ");
                await msg.ShowAsync();
            }

        }

        private void Grid_Tapped_1(object sender, TappedRoutedEventArgs e)
        {
            appbar.IsOpen = false;
        }

        private void txtTaskDescription_GotFocus(object sender, RoutedEventArgs e)
        {
            appbar.IsOpen = false;
        }

        /*private async void bttnSave_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                EnsureUnsnapped();
                if (unSnapped)
                {
                    Windows.Storage.StorageFolder documentFolder = KnownFolders.DocumentsLibrary;
                    var file = await documentFolder.CreateFileAsync("ToDo.txt", CreationCollisionOption.ReplaceExisting);
                    if (file != null)
                    {
                        string contents = "";
                        foreach (ToDos td in toDosCollection)
                        {
                            contents += "Description:\t" + td.TaskDescription + Environment.NewLine + "Category:\t" + td.TaskCategory + Environment.NewLine + "Dead Line:\t" + td.TaskDeadLine + Environment.NewLine + Environment.NewLine + "*****************" + Environment.NewLine + Environment.NewLine;
                        }
                        await Windows.Storage.FileIO.WriteTextAsync(file, contents);
                        MessageDialog msg = new MessageDialog("Tasks saved in the Documents Library in a file named ToDo.txt");
                        await msg.ShowAsync();
                    }
                }
            }
            catch { }
        }*/
        private async void bttnSave_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                EnsureUnsnapped();
                if (unSnapped)
                {
                    //Windows.Storage.StorageFolder documentFolder = KnownFolders.DocumentsLibrary;   
                    StorageFolder documentFolder = ApplicationData.Current.LocalFolder;
                    StorageFile file = await documentFolder.CreateFileAsync("ToDo.txt", CreationCollisionOption.ReplaceExisting);
                    if (file != null)
                    {
                        string contents = "";
                        foreach (ToDos td in toDosCollection)
                        {
                            contents += "Description:\t" + td.TaskDescription + Environment.NewLine + "Category:\t" + td.TaskCategory + Environment.NewLine + "Dead Line:\t" + td.TaskDeadLine + Environment.NewLine + Environment.NewLine + "*****************" + Environment.NewLine + Environment.NewLine;
                        }
                        await Windows.Storage.FileIO.WriteTextAsync(file, contents);
                        MessageDialog msg = new MessageDialog("Tasks saved in the Documents Library in a file named ToDo.txt");
                        await msg.ShowAsync();
                    }
                }
            }
            catch { }
        }
    }
}
