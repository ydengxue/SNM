#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unordered_set>

#define WR_BUFFER_SIZE 32
#define WR_TICK_ONE_TIME 500

using namespace std;

int main(int argc, char *argv[])
{
	char input[80];
	string filelocation;
	ifstream infile;  // read to open file
    unordered_set<string> wr_buffer1;
    unordered_set<string> wr_buffer2;
    int  write_buf1;
    int  write_buf2;
    int  index_w;
    int  write_num;
    long long tick;
    long long tick_last;
    int i;
    int vol;
    int vol_last;
    long long sw1_cnt;
    long long sw2_cnt;

    if (argc < 2) {
        cout << "input error!\r\n" << endl;
        return -1;
    }
	infile.open(argv[1]); //input the name of the file which is opened

	if(!infile.is_open())
	{
		cout<<"Can not open the file"<<endl;
		return 0;
	}

    write_buf1 = 0;
    write_buf2 = 0;
    index_w = 0;
    write_num = 0;
    tick = 0;
    tick_last = 0;
    vol = 0;
    vol_last = 0;
	while(infile.getline(input, 80))
	{
        input[79] = '\0';

        char *p_ins;
        char *p_str;
        char *p_str1;
        p_str = strchr(input, ',');
        p_ins = p_str + 1;
        p_str = strchr(p_ins, ',');
        *p_str = '\0';

        p_str++;
        p_str = strchr(p_str, ',');
        p_str++;
        p_str = strchr(p_str, ',');
        p_str++;

        tick = atoll(p_str);
        write_num = (tick - tick_last) / WR_TICK_ONE_TIME;
        tick_last = tick;

        vol = 0;
		if (wr_buffer1.size() >= WR_BUFFER_SIZE)
		{
            vol = 1;
            write_buf1 = 1;
            write_buf2 = 0;
            for (i = 0; i < write_num; i++)
            {
                index_w++;
                if (index_w >= WR_BUFFER_SIZE)
                {
                    index_w = 0;
                    write_buf1 = 2;
                    wr_buffer1.clear();
                    break;
                }
            }
        }
        else if (wr_buffer2.size() >= WR_BUFFER_SIZE)
		{
            vol = 1;
            write_buf1 = 0;
            write_buf2 = 1;
            for (i = 0; i < write_num; i++)
            {
                index_w++;
                if (index_w >= WR_BUFFER_SIZE)
                {
                    index_w = 0;
                    write_buf2 = 2;
                    wr_buffer2.clear();
                    break;
                }
            }
        }

        if (vol_last != vol) {
            if (vol) {
                sw1_cnt++;
            }
            else
            {
                sw2_cnt++;
            }
        }

        vol_last = vol;

//        for (i = 0; i < write_num; i++)
//        {
//            cout << vol;
//        }

		if ('w' == input[0])
		{
            if (!write_buf1)
            {
			    if (wr_buffer1.count(p_ins))
			    {
				    continue;
			    }
			    wr_buffer1.insert(p_ins);
            }
            else
            {
			    if (wr_buffer2.count(p_ins))
			    {
				    continue;
			    }
			    wr_buffer2.insert(p_ins);
            }
		}
		else
		{
			if (wr_buffer1.count(p_ins))
			{
				continue;
			}
			if (wr_buffer2.count(p_ins))
			{
				continue;
			}
		}
	}

    cout << "0->1 count: " << sw1_cnt << endl;
    cout << "1->0 count: " << sw2_cnt << endl;

	return 0;
}
