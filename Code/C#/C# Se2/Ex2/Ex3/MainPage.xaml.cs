using System;
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
using System.Collections.ObjectModel;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace Ex3
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public class CustomImage
    {
        public string imgURL { get; set; }
        public string imgName { get; set; }
        public bool isEnabled { get; set; }
        public CustomImage(string url, string name, bool enable = true)
        {
            imgURL = url;
            imgName = name;
            isEnabled = enable;
        }
    }

    public sealed partial class MainPage : Page
    {
        //Declare the variable that stores the target on which an
        //image is going to be dropped on the right hand side tiles.
        Image probableDropTarget = null;
        //Create a collection to stroe the left hand side images
        ObservableCollection<CustomImage> sourceImages = new ObservableCollection<CustomImage>();
        //Create a collection to store right hand side images
        ObservableCollection<CustomImage> destImages = new ObservableCollection<CustomImage>();
        //Create a variable to store dragged image
        IList<object> DraggedItems;
        //Determine whether the user has dropped the image being dragged
        bool isDragging = false;
        //Determine the total number of images dragged
        int imagesDragged = 0;
        public MainPage()
        {
            this.InitializeComponent();
            //Add images to the ObservableCollection sourceImages
            sourceImages.Add(new CustomImage("Images/Part1.jpg", "0"));
            sourceImages.Add(new CustomImage("Images/Part2.jpg", "1"));
            sourceImages.Add(new CustomImage("Images/Part3.jpg", "2"));
            sourceImages.Add(new CustomImage("Images/Part4.jpg", "3"));
            sourceImages.Add(new CustomImage("Images/Part5.jpg", "4"));
            sourceImages.Add(new CustomImage("Images/Part6.jpg", "5"));
            sourceImages.Add(new CustomImage("Images/Part7.jpg", "6"));
            sourceImages.Add(new CustomImage("Images/Part8.jpg", "7"));
            sourceImages.Add(new CustomImage("Images/Part9.jpg", "8"));
            //Bind the images added in the sourceImages ObservableCollection to
            //the GridView grdSourceImages by setting its ItemsSource property
            grdSourceImages.ItemsSource = sourceImages;
            //Add images to the ObservableCollection destImages
            destImages.Add(new CustomImage("Images/tileBackground.png", "0"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "1"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "2"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "3"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "4"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "5"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "6"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "7"));
            destImages.Add(new CustomImage("Images/tileBackground.png", "8"));
            //Bind the images added in the destImages ObservableCollection to
            //the GridView grdSourceImages by setting its ItemsSource property
            grdDestImages.ItemsSource = destImages;
        }

        private void grdSourceImages_DragItemsStarting(object sender, DragItemsStartingEventArgs e)
        {
            //Retrieve a reference of the image being dragged
            DraggedItems = e.Items;
            isDragging = true;
            appbarGameCommands.IsOpen = false;
        }

        private void grdDestImages_Drop(object sender, DragEventArgs e)
        {
            isDragging = false;
            foreach (Object O in DraggedItems)
            {
                //Retrieve the image being dragged
                CustomImage sourceImage = O as CustomImage;
                //Check if the block on which the image is being dragged is 
                //enabled for dropping the image
                if (destImages[Convert.ToInt32(probableDropTarget.Tag)].isEnabled)
                {
                    //Disable the block in the source grid from where
                    //the image has been dragged
                    sourceImage.isEnabled = false;
                    //Remove the dragged image form source grid
                    sourceImages.Remove(sourceImage);
                    //Insert a blank image in the block from where the dragged image is removed
                    sourceImages.Insert(Convert.ToInt32(sourceImage.imgName), new CustomImage("Images/tileBackground.png", sourceImage.imgName, false));
                    grdSourceImages.ItemsSource = sourceImages;
                    sourceImage.imgName = probableDropTarget.Tag as string;
                    //Remove the current image in the block on which the image has been dropped
                    destImages.RemoveAt(Convert.ToInt32(probableDropTarget.Tag));
                    //Insert the dragged image in the block on which it is dropped
                    destImages.Insert(Convert.ToInt32(probableDropTarget.Tag), sourceImage);
                    grdDestImages.ItemsSource = destImages;
                    imagesDragged++;

                }
            }
            //Check if all the images have been dragged and dropped
            if (imagesDragged == 9)
                showResult();
        }

        private void Showhintimage_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(HintPage));
        }

        private void Reset_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private void Image_DragEnter(object sender, DragEventArgs e)
        {
            //Check if the image is being dragged over a block in the 
            //destination grid
            if (isDragging)
            {
                //Set the block on which the image has entered, while
                //dragging, as the probable drop target of the image
                probableDropTarget = sender as Image;
            }
        }

        void showResult()
        {
            //Disable drop operation of the destination grid
            grdDestImages.AllowDrop = false;
            //Disable the drag operation of the source grid
            grdSourceImages.CanDragItems = false;
            //Determine if the player has dragged the images at correct position
            if(destImages[0].imgURL.EndsWith("Part1.jpg") && 
                destImages[1].imgURL.EndsWith("Part4.jpg") &&
                destImages[2].imgURL.EndsWith("Part7.jpg") && 
                destImages[3].imgURL.EndsWith("Part2.jpg") && 
                destImages[4].imgURL.EndsWith("Part5.jpg") && 
                destImages[5].imgURL.EndsWith("Part8.jpg") && 
                destImages[6].imgURL.EndsWith("Part3.jpg") && 
                destImages[7].imgURL.EndsWith("Part6.jpg") && 
                destImages[8].imgURL.EndsWith("Part9.jpg"))
            {
                //If the user has dragged the images at correct position, display
                //the winning message
                txtblkStatus.Text = "Congratulations, You Won the Game!!";
            }
            else
            {
                txtblkStatus.Text = "You Lost the Game!! Try Again!!";
                appbarGameCommands.IsOpen = true;
            }
        }
    }
}
