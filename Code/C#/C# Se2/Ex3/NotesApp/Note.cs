using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;

namespace NotesApp
{

    class NotesCollection
    {
        public static ObservableCollection<Note> Notes = new ObservableCollection<Note>();
    }
    class Note
    {
        public string Title { get; set; }
        public string Content { get; set; }
        public Note(string Title, string Content)
        {
            this.Title = Title;
            this.Content = Content;
        }
    }
}