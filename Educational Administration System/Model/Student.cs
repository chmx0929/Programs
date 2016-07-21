using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Model
{
    public class Student:User
    {
        private string grade;
        private Course[] course;
        public string Grade
        {
            get { return this.grade; }
            set { this.grade = value; }
        }
        public Course[] Course
        {
            get { return this.course; }
            set { this.course = value; }
        }
    }
}
