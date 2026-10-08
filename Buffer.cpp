#include <fstream>

#include "Buffer.hpp"

namespace sjtu {

Buffer::Buffer(const std::filesystem::path& path){
    //从path指向的文件构造Buffer,你需要打开文件并且把文件内容填充进Buffer,并正确初始化一些状态.
    //注意path可能为空的边界情况
    if (path.empty())
    {
        lines_.push_back("");
    }
    else
    { 
        std::ifstream file (path);
        
        
            std::string line;
            while (std::getline(file, line))
            {
                lines_.push_back(line);
            }
        
    
    if (lines_.empty())
    {
        lines_.push_back("");
    }}

}

Buffer::Buffer(std::vector<std::string> lines, std::filesystem::path path) {
    lines_=std::move(lines);
    path_=std::move(path);
    if (lines_.empty())
    {
        lines_.push_back("");
    }

}
std::size_t Buffer::GetLineCount() const {
    //返回文件行数
    return lines_.size();
}

const std::string& Buffer::GetLineAt(std::size_t row) const {
    //返回第row行的内容
    if (row >= GetLineCount())
    {
    std::cerr<<"Index out of range!"<<std::endl;
    }
    else
    return lines_[row-1];
}


 std::string Buffer::GetDisplayName() const {
    //返回文件名,若是新文件,返回"[No Name]"
    if (path_.empty())
    {
        return "[No Name]";
    }
    else
    return path_.filename().string();

    }

bool Buffer::IsModified() const {
    //返回文件和上次保存比起来是否被修改过
    if (path_.empty())
    return true;
    else
    {
       std::ifstream file(path_);
            std::string line;
            std::vector<std::string> lines;

            while (std::getline(file,line))
            {lines.push_back(line_);}
            if (lines_.size()!=lines.size())
            {return true;}
            else
            {
                for(int i=0;i<line.size();i++)
                {if (lines_[i]!=lines[i])
                return true;}

            }

            
            


    };
    return false;
}
void Buffer::InsertCharacter(std::size_t row, std::size_t column, char value) {
    //在第row行第col列插入一个value, 注意越界检查
   lines_[row-1].insert(column-1,1,value);
}

void Buffer::EraseCharacter(std::size_t row, std::size_t column) {
   //在第row行第col列删除一个value
   lines_[row-1].erase(column-1,1);
}

void Buffer::SplitLine(std::size_t row, std::size_t column) {
    //在第row行第col列分割,即在此处敲了回车键
    std::string s1=lines_[row-1].substr(0,column-1);
    std::string s2=lines_[row-1].substr(column-1);
    lines_[row-1]=s1;
    lines_.insert(lines_.begin()+row, s2);
}

void Buffer::JoinLine(std::size_t row) {
   //把第row + 1行合并进第row行
   lines_[row-1]+=lines_[row];
   lines_.erase(lines_.begin()+row);
}

void Buffer::Save() {
   //把文件内容保存, 直接调用WriteTo方法
   WriteTo(path_);
}

void Buffer::SaveAs(const std::filesystem::path& path) {
    WriteTo(path_);
    path_=path;
}


void Buffer::WriteTo(const std::filesystem::path& path) const {
   //实际将缓冲区中的内容写入path指向的文件中
   if(path.empty())
   {
    std::cerr<<"Path is empty!"<<std::endl;
   }
   else{
    std::ofstream temfile(path);
    if(temfile.is_open())
    {
        for(auto &line:lines_)
        {
            temfile<<line<<std::endl;
        }
    }
    else
    {
        std::cerr<<"File open error!"<<std::endl;
    }
   }
}

} // namespace sjtu
