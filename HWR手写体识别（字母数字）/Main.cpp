#include "Net.h"
#include "FakeQueue.h"

int random(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

// 创建神经网络对象
/* 28x28 */
NeuralNetwork nn(784, 200, 62, 0.1);

char Text[] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
string Name[] = { "0.png","1.png","2.png","3.png","4.png","5.png","6.png","7.png","8.png","9.png","a.png","b.png","c.png","d.png","e.png","f.png","g.png","h.png","i.png","j.png","k.png","l.png","m.png","n.png","o.png","p.png","q.png","r.png","s.png","t.png","u.png","v.png","w.png","x.png","y.png","z.png","Upa.png","Upb.png","Upc.png","Upd.png","Upe.png","Upf.png","Upg.png","Uph.png","Upi.png","Upj.png","Upk.png","Upl.png","Upm.png","Upn.png","Upo.png","Upp.png","Upq.png","Upr.png","Ups.png","Upt.png","Upu.png","Upv.png","Upw.png","Upx.png","Upy.png","Upz" };
string FontName[] = { "Freestyle Script常规","Brush ScriptMT斜体","Gabriola常规","Ink Free常规","Lucida Handwriting 斜体","Mistral常规","OCR A 展开","华文行楷 常规","华文隶书 常规","仿宋 常规","Pristina常规","Arial"};

void Print()
{
    setfillcolor(WHITE);
    solidrectangle(29, 9, 231, 111);
    for (int i = 0; i < 200; i++)
    {
        setlinecolor(ffb[i]?GREEN:RED);
        line(30 + i, 110 - (100.0 * ff[i]),30 + i, 110);
    }
}
void TrainTTF()
{
    IMAGE TrainImage(28, 28);
    float countall = 1, yes = 0;
    for (int f = 0; f < 12; f++)
        for (int i = 0; i < 62; i++, countall++)
        {
            SetWorkingImage(&TrainImage);
            setfillcolor(WHITE);
            settextcolor(BLACK);
            setbkcolor(WHITE);
            solidrectangle(0, 0, 28, 28);
            settextstyle(16 + random(-5, 5), 20 + random(-5, 5), FontName[f].c_str());
            outtextxy(random(0, 7), random(0, 3), Text[i]);
            SetWorkingImage(NULL);
            putimage(0, 0, &TrainImage);
            nn.train(TrainImage, Text[i]);
            char ch = nn.predict(TrainImage);
            if (ch == Text[i]) yes++;
            cout << FontName[f] << "-" << Text[i] << "|预测结果-" << ch << ((ch == Text[i]) ? " [Yes]" : " [No]") << " | " << "成功率" << 100.0 * (yes / countall) << "%\n";
            settextstyle(29, 15, "微软雅黑");
            setfillcolor(BLACK);
            solidrectangle(0, 30, 29, 80);
            settextcolor(LIGHTBLUE);
            outtextxy(0, 30, Text[i]);
            outtextxy(0, 55, ch);
            settextcolor(ch == Text[i] ? GREEN : RED);
            outtextxy(0, 80, ch == Text[i] ? "Y" : "N");
            push(yes / countall, ch == Text[i]);
            Print();
            char cgl[20];
            _gcvt_s(cgl, yes / countall, 10);
            settextcolor(WHITE);
            settextstyle(9, 4, "微软雅黑");
            outtextxy(55, 0, cgl);
        }
}
void TrainHD()
{
    SetWorkingImage(NULL);
    IMAGE TrainImage(28, 28);
    float countall = 0, yes = 0;
    for (int i = 0; i < 62; i++, countall++)
    {
        loadimage(&TrainImage, (".\\Train-HandDraw\\1\\" + Name[i]).c_str());
        putimage(0, 0, &TrainImage);
        nn.train(TrainImage, Text[i]);
        char ch = nn.predict(TrainImage);
        if (ch == Text[i]) yes++;
        cout << "序列1" << "-" << Text[i] << "|预测结果-" << ch << ((ch == Text[i]) ? " [Yes]" : " [No]") << " | " << "成功率" << 100.0 * (yes / countall) << "%\n";
        settextstyle(29, 15, "微软雅黑");
        setfillcolor(BLACK);
        solidrectangle(0, 30, 29, 80);
        settextcolor(LIGHTBLUE);
        outtextxy(0, 30, Text[i]);
        outtextxy(0, 55, ch);
        settextcolor(ch == Text[i] ? GREEN : RED);
        outtextxy(0, 80, ch == Text[i] ? "Y" : "N");
        push(yes / countall, ch == Text[i]);
        Print();
        char cgl[20];
        _gcvt_s(cgl, yes / countall, 10);
        settextcolor(WHITE);
        settextstyle(9, 4, "微软雅黑");
        outtextxy(55, 0, cgl);
        
    }
}

int main()
{
    int command;
    ios::sync_with_stdio(false);
    while (1)
    {
        cout << "1-字体库训练 2-读取节点信息 3-保存节点信息 4-手写库训练 5-字体识别" << endl;
        cin >> command;
        switch (command)
        {
        case 1:
        {
            int c;
            cout << "循环次数" << endl;
            cin >> c;
            initgraph(232, 112, 1);
            for(int i=0;i<c;i++)
                TrainTTF();
            closegraph();
            break;
        }
        case 2:
        {
            nn.load_parameters("parameters.txt");
            break;
        }
        case 3:
        {
            nn.save_parameters("parameters.txt");
            break;
        }
        case 4:
        {
            int c;
            cout << "循环次数" << endl;
            cin >> c;
            initgraph(232, 112, 1);
            for (int i = 0; i < c; i++)
                TrainHD();
            closegraph();
            break;
        }
        case 5:
        {

            break;
        }
        }
    }
    return 0;
}
/*int main() {


    // 读取保存的神经网络参数
    nn.load_parameters("parameters.txt");

    // 训练神经网络
    nn.train("0.png", '0');
    nn.train("1.png", '1');
    nn.train("2.png", '2');
    // ...
    nn.train("a.png", 'a');
    nn.train("b.png", 'b');
    nn.train("c.png", 'c');
    // ...
    nn.train("A.png", 'A');
    nn.train("B.png", 'B');
    nn.train("C.png", 'C');
    // ...

    // 保存神经网络参数
    nn.save_parameters("parameters.txt");

    // 使用神经网络
    char result = nn.predict("test.png");
    cout << "The prediction result is: " << result << endl;

    closegraph();
    return 0;
}*/