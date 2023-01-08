#include <string>
#include <vector>

std::vector<std::string> split(const char str[], char delim, int max_split = 0){
    std::vector<std::string> split_string{};
    std::string temp;
    if (max_split == 0){
        for (const char* s = str; *s != '\0'; s++){
            if (*s != delim){
                temp += *s;
            }
            else {
                split_string.push_back(temp);
                temp = "";
            }
        }
        split_string.push_back(temp);
    }
    else {
        int j{};
        for (const char* i = str; *i != '\0'; i++){
            if (j != max_split){
                if (*i == delim){
                    split_string.push_back(temp);
                    temp = "";
                    j++;
                    continue;
                }
                else {
                    temp += *i;
                }
                continue;
            }
             while (*i != '\0'){
                 temp += *i;
                 i++;
             }
             split_string.push_back(temp);
             break;
        }
    }
    return split_string;
}