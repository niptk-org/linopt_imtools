#include "CommandLineInterface/CLIcore.h"




// Local variables pointers
static char *inimname;
static char *inpixiname;
static char *inpixmultname;
static char *outvecname;



static CLICMDARGDEF farg[] =
{
    {
        CLIARG_IMG, ".inim", "input image", "im",
        CLIARG_VISIBLE_DEFAULT,
        (void **) &inimname
    },
    {
        CLIARG_IMG, ".inpixi", "input pixel index image", "pixi",
        CLIARG_VISIBLE_DEFAULT,
        (void **) &inpixiname
    },
    {
        CLIARG_IMG, ".inpixmult", "input pixel mult image", "pixmult",
        CLIARG_VISIBLE_DEFAULT,
        (void **) &inpixmultname
    },
    {
        CLIARG_STR, ".outvec", "output vector image", "vecim",
        CLIARG_VISIBLE_DEFAULT,
        (void **) &outvecname
    }
};

static CLICMDDATA CLIcmddata =
{
    "im2vec",
    "remap image to vector",
    CLICMD_FIELDS_DEFAULTS
};


// detailed help
static errno_t help_function()
{
    return RETURN_SUCCESS;
}



//
//
//
imageID linopt_imtools_image_to_vec(
    const char *ID_name,
    const char *IDpixindex_name,
    const char *IDpixmult_name,
    const char *IDvec_name
)
{
    DEBUG_TRACE_FSTART();

    imageID ID;
    long k;
    imageID IDpixindex, IDpixmult;
    imageID IDvec;
    long NBpix;
    long naxisin;
    long sizexy;
    uint8_t datatype;

    ID = image_ID(ID_name);
    naxisin = data.image[ID].md[0].naxis;
    datatype = data.image[ID].md[0].datatype;


    IDpixindex = image_ID(IDpixindex_name);
    IDpixmult = image_ID(IDpixmult_name);
    NBpix = data.image[IDpixindex].md[0].nelement;

    if(naxisin < 3)
    {
        FUNC_CHECK_RETURN(
            create_2Dimage_ID(IDvec_name, NBpix, 1, &IDvec));
        for(k = 0; k < NBpix; k++)
        {
            data.image[IDvec].array.F[k] = data.image[IDpixmult].array.F[k] *
                                           data.image[ID].array.F[data.image[IDpixindex].array.SI64[k]];
        }
    }
    else
    {
        sizexy = data.image[ID].md[0].size[0] * data.image[ID].md[0].size[1];
        if(datatype == _DATATYPE_FLOAT)
        {
            FUNC_CHECK_RETURN(
                create_2Dimage_ID(IDvec_name, NBpix, data.image[ID].md[0].size[2], &IDvec));

            for(uint32_t kk = 0; kk < data.image[ID].md[0].size[2]; kk++)
                for(k = 0; k < NBpix; k++)
                {
                    data.image[IDvec].array.F[kk * NBpix + k] = data.image[IDpixmult].array.F[k] *
                            data.image[ID].array.F[kk * sizexy + data.image[IDpixindex].array.SI64[k]];
                }
        }
        if(datatype == _DATATYPE_COMPLEX_FLOAT)
        {
            FUNC_CHECK_RETURN(
                create_2Dimage_ID(IDvec_name, NBpix * 2, data.image[ID].md[0].size[2], &IDvec));

            for(uint32_t kk = 0; kk < data.image[ID].md[0].size[2]; kk++)
                for(k = 0; k < NBpix; k++)
                {
                    data.image[IDvec].array.F[kk * NBpix * 2 + 2 * k] =
                        data.image[IDpixmult].array.F[k] * data.image[ID].array.CF[kk * sizexy +
                                data.image[IDpixindex].array.SI64[k]].re;
                    data.image[IDvec].array.F[kk * NBpix * 2 + 2 * k + 1] =
                        data.image[IDpixmult].array.F[k] * data.image[ID].array.CF[kk * sizexy +
                                data.image[IDpixindex].array.SI64[k]].im;
                }
        }

    }

    DEBUG_TRACE_FEXIT();
    return ID;
}



static errno_t compute_function()
{
    DEBUG_TRACE_FSTART();

    INSERT_STD_PROCINFO_COMPUTEFUNC_START

    linopt_imtools_image_to_vec(
        inimname,
        inpixiname,
        inpixmultname,
        outvecname
    );

    INSERT_STD_PROCINFO_COMPUTEFUNC_END

    DEBUG_TRACE_FEXIT();
    return RETURN_SUCCESS;
}




INSERT_STD_FPSCLIfunctions

// Register function in CLI
errno_t CLIADDCMD_linopt_imtools__image_to_vec()
{
    INSERT_STD_CLIREGISTERFUNC
    return RETURN_SUCCESS;
}
