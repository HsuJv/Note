using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;

namespace ClasstableTable
{

    class NotesCollection
    {
        public static ObservableCollection<Homework> Notes = new ObservableCollection<Homework>();
    }
    class Homework
    {
        public string Title { get; set; }
        public string Content { get; set; }
        public string Deadline { get; set; }
        public string Usrname { get; set; }
        public Homework(string Title, string Content, string Deadline, string Usrname)
        {
            this.Title = Title;
            this.Content = Content;
            this.Deadline = Deadline;
            this.Usrname = Usrname;
        }
    }
}
