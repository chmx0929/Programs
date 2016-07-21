using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Model;
using System.Data;
using System.Data.SqlClient;

namespace DAL
{
    public class Select
    {
        //score
        public static DataTable selectScoresByStudent(Student s)//student
        {
            string str = "select courseID,course.name course,teacher.name teacher,score from course,score,teacher where studentID='" + s.Id + "' and courseID=course.id and teacherID=teacher.id";
            return new DataBase().GetDataTable(str);
        }
        public static DataSet selectScoresByTeacher(Teacher t)//Teacher
        {
            DataBase db = new DataBase();
            int i = 0;
            string str = "select id,name from course where teacherID='" + t.Id + "'";
            SqlDataReader myReader = db.GetDataReader(str);
            DataSet ds = new DataSet();
            if (myReader.HasRows == false)
            {
                return ds;
            }
            else
                while (myReader.Read())
                {
                    db.GetAddDataSet(ds, "select studentID,student.name,score from score,student where student.id=studentID and courseID='" + (string)myReader["id"] + "'");
                    ds.Tables[i].Columns.Add("courseID");
                    ds.Tables[i].Columns.Add("course");
                    ds.Tables[i].Columns["courseID"].SetOrdinal(0);
                    ds.Tables[i].Columns["course"].SetOrdinal(1);
                    ds.Tables[i].Rows[0].BeginEdit();
                    DataRow dr = ds.Tables[i].Rows[0];
                    dr.BeginEdit();
                    dr["courseID"] = (string)myReader["id"];
                    dr["course"] = (string)myReader["name"];
                    dr.EndEdit();
                    i++;
                }
            return ds;
        }
        public static DataTable selectScoresByCourse(Course c)//Teacher
        {
            string str = "select studentID,student.name,score from score,student where student.id=studentID and courseID='" + c.Id + "'";
            return new DataBase().GetDataTable(str);
        }

        //course
        public static DataTable selectCourses()//manager
        {
            string str="select id,name,teacherID from course";
            return new DataBase().GetDataTable(str);
        }
        public static SqlDataReader selectChoosableCoursesByStudent(Student s) //student
        {
            string str = "select id,name,teacherID from course,score where id!=courseID and studentID='"+s.Id+"'";
            return new DataBase().GetDataReader(str);
        }
        public static SqlDataReader selectCoursesByTeacher(Teacher t)//teacher
        {
            string str = "select id,name from course where teacherID='" + t.Id + "'";
            return new DataBase().GetDataReader(str);
        }


        //user
        public static User checkUser(User u)
        {
            string str = "select id,name,password from " + u.Identity + " where id='" + u.Id + "'and password='" + u.Password + "'";
            SqlDataReader sdr=new DataBase().GetDataReader(str);
            if (sdr.HasRows == false)
                return null;
            else
            {
                sdr.Read();
                u.Name=(string)sdr["name"];
                return u;
            }
        }


        //student
        public static DataTable selectStudents(int i)//manager
        {
            string str = "select * from student";
            return new DataBase().GetDataTable(str);
        }
        public static SqlDataReader selectStudents()//manager
        {
            string str = "select * from student";
            return new DataBase().GetDataReader(str);
        }
        public static SqlDataReader selectStudentsByCourse(Course c)//teacher
        {
            string str = "select id,name from student where id=(select studentID from score where courseID=(select id from course where id='" + c.Id + "'))";
            return new DataBase().GetDataReader(str);
        }
        public static string selectStudentNameById(string id)//teacher
        {
            string str = "select name from student where id='" + id + "'";
            SqlDataReader sdr = new DataBase().GetDataReader(str);
            if(sdr.Read())
            return (string)sdr["name"];
            return null;
        } 

        //teacher
        public static DataTable selectTeachers(int i)//manager
        {
            string str = "select * from teacher";
            return new DataBase().GetDataTable(str);
        }
        public static SqlDataReader selectTeachers()//manager
        {
            string str = "select * from teacher";
            return new DataBase().GetDataReader(str);
        }
        //manager
    }
}
