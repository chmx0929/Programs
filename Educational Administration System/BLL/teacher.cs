using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DAL;
using Model;
using System.Data;
using System.Data.SqlClient;

namespace BLL
{
    public class teacher
    {
        public Boolean changePassword(Teacher t,string str)
        {
            t.Password = str;
            return Update.updateTeacher(t);
        }
        public DataSet selectAllScores(Teacher t)
        {
            return Select.selectScoresByTeacher(t);
        }
        public DataTable selectScoresByCourse(Course c)
        {
            return Select.selectScoresByCourse(c);
        }
        public string selectNameById(string id)
        {
            return Select.selectStudentNameById(id);
        }
        public Boolean update(string c_id, string s_id, int score)
        {
            Score s = new Score();
            s.CourseID = c_id;
            s.StudentID = s_id;
            s._Score = score;
            return Update.updateScore(s);
        }
        public SqlDataReader selectStudentByCourse_ID(Course c)
        {
            return Select.selectStudentsByCourse(c);
        }
        public SqlDataReader selectCourseByTeacher(Teacher t)
        {
            return Select.selectCoursesByTeacher(t);
        }
        public DataSet order(DataSet ds, string name, string by)
        {
            DataSet newds = new DataSet();

            for (int i = 0; i < ds.Tables.Count; i++)
            {
                DataView dv = new DataView();
                DataTable dt = new System.Data.DataTable();
                dv.Table = ds.Tables[i];
                dv.Sort = name + " " + by;
                dt = dv.ToTable();
                newds.Tables.Add(dt);
            }
            return newds;
        }
    }
}
