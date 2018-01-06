array deep_file_list(string dir) 
{ 
        int i; 
        array flist, result = ({ }); 
        string file; 
   
        flist = get_dir(dir); 

        for (i = 0; i < sizeof(flist); i++) 
        { 
                file = dir + flist[i]; 
           
                if (file_size(file + "/") == -2) 
                        result += deep_file_list(file + "/"); 
                else  
                        result += ({ file }); 
        
        } 
        return result; 
} 


void change()
{
        int i;
        array dir;
        string file;
        
        dir = deep_file_list("/data/item/");
        for(i=0; i<sizeof(dir); i++) 
        { 
                reset_eval_cost(); 
                if ( file_size(dir[i]) > 0) 
                {
                        file = read_file(dir[i]);
                        file = replace_string(file, "msg\", \"", "msg\", \"��");
                        file = replace_string(file, "\\n", "\n��"); 
                        file = replace_string(file, "��\")", "\")");
                        rm(dir[i]);
                        write_file(dir[i], file);
                } 
        } 
}

