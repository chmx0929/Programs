using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Model
{
    public class Course
    {
        private string id;
        private string name;
        private string teacherID;
        public string Id
        {
            get { return this.id; }
            set { this.id = value; }
        }
        public string Name
        {
            get { return this.name; }
            set { this.name = value; }
        }
        public string TeacherID
        {
            get { return this.teacherID; }
            set { this.teacherID = value; }
        }
    }
}
