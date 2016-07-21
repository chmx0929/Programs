using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DAL
{
    public class Score
    {
        private string courseID;
        private string studentID;
        private int score;
        public string CourseID
        {
            get { return this.courseID; }
            set { this.courseID = value; }
        }
        public string StudentID
        {
            get { return this.studentID; }
            set { this.studentID = value; }
        }
        public int _Score
        {
            get { return this.score; }
            set { this.score = value; }
        }
    }
}
