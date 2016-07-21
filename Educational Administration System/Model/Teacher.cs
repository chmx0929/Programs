using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Model
{
    public class Teacher:User
    {
        private Course course=new Course();
        public Course Course
        {
            get { return this.course; }
            set { this.course = value; }
        }

    }
}