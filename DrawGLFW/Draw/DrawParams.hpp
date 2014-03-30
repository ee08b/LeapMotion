#ifndef DRAWPARAMS_H
#define DRAWPARAMS_H

class DrawParams
{
    public:
        static DrawParams* getInstance();
        
        double rotate_y; 
        double rotate_x;
        double rotate_z;

        double translate_y;
        double translate_x;
        double translate_z;

        float scale;

    private:
	static DrawParams* instance; 
        DrawParams();
        DrawParams(DrawParams const&);
        void operator=(DrawParams const&);
};

#endif /* end of include guard: DRAWPARAMS_H */
