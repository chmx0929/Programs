using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Model;
using System.Data;
using System.Data.SqlClient;

namespace DAL
{
    public class Delete
    {
        public static bool deleteStudent(Student s)
        {
            string str = "delete  from student where id ='" + s.Id + "'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static bool deleteTeacher(Teacher t)
        {
            string str1 = "delete  from teacher where id ='" + t.Id + "'";
            string str2 = "delete from course where teacherID='"+t.Id+"'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str1);
                db.RunSql(str2);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static bool deleteManager(Manager m)
        {
            string str = "delete  from manager where id ='" + m.Id + "'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static bool deleteScore(Score s) 
        {
            string str = "delete  from score where courseID ='" + s.CourseID + "' and studentID='" + s.StudentID + "'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
    }
}
