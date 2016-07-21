using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Model;
using System.Data;
using System.Data.SqlClient;

namespace DAL
{
    public class Insert
    {
        public static bool insertStudent(Student s)
        {
            string str1 = "insert into student values ('" + s.Id + "','" + s.Name + "','" + s.Password + "')";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str1);   
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static bool insertTeacher(Teacher t)
        {
            string str1 = "insert into teacher values ('" + t.Id + "','" + t.Name + "','" + t.Password + "')";
            string str2 = "insert into course (name,teacherID) values('"+t.Course.Name+"','"+t.Id+"')";
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
        public static bool insertManager(Manager m)
        {
            string str = "insert into manager values ('" + m.Id + "','" + m.Name + "','" + m.Password + "')";
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
        public static bool insertCourse(Course c)
        {
            string str = "insert into course (id,name) values ('" + c.Id + "','" + c.Name + "')";
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
        public static bool insertScore(Score s) 
        {
            string str = "insert into score (courseID,studentID) values ('" + s.CourseID + "','" + s.StudentID + "')";
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
