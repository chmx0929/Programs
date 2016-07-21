using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DAL;
using System.Data;
using System.Data.SqlClient;
using Model;

namespace BLL
{
    public class student
    {
        public Boolean changePassword(Student s, string str)
        {
            s.Password = str;
            return Update.updateStudent(s);
        }
        public  DataTable selectScores(Student s)
        {
            return Select.selectScoresByStudent(s);
        }
        public SqlDataReader showChoosableCourses(Student s)
        {
            return Select.selectChoosableCoursesByStudent(s);
        }
        public Boolean chooseCourse(Student s,Course c)
        {
            Score score=new Score();
            score.StudentID = s.Id;
            score.CourseID = c.Id;
            return Insert.insertScore(score);
        }
    }
}
