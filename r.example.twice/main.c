#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <grass/gis.h>
#include <grass/glocale.h>
#include <grass/raster.h>

static double times_two(double a)
{
    return 2 * a;
}

int main(int argc, char *argv[])
{
    struct Cell_head cell_head;
    struct History history;
    char *name;                 /* input raster name */
    char *result;               /* output raster name */
    char *mapset;               /* mapset name */
    void *input_raster;               /* input buffer */
    unsigned char *output_raster;     /* output buffer */
    int nrows, ncols;
    int row, col;
    int input_fd, output_fd;            /* file descriptor */
    RASTER_MAP_TYPE data_type;  /* type of the map (CELL/DCELL/...) */

    // Initilizes the GRASS library based on the current GRASS session
    G_gisinit(argv[0]);

    // Interface
    struct GModule *module = G_define_module();
    G_add_keyword(_("raster"));
    G_add_keyword(_("algebra"));
    G_add_keyword(_("multiplication"));
    module->description = _("Multiply values in a raster map by two");

    struct Option *input = G_define_standard_option(G_OPT_R_INPUT);
    struct Option *output = G_define_standard_option(G_OPT_R_OUTPUT);

    if (G_parser(argc, argv))
        exit(EXIT_FAILURE);

    /* stores options and flags to variables */
    name = input->answer;
    result = output->answer;

    /* returns NULL if the map was not found in any mapset, 
     * mapset name otherwise */
    mapset = (char *)G_find_raster2(name, "");
    if (mapset == NULL)
        G_fatal_error(_("Raster map <%s> not found"), name);

    /* determine the input map type (CELL/FCELL/DCELL) */
    data_type = Rast_map_type(name, mapset);

    /* Rast_open_old - returns file descriptor (>0) */
    input_fd = Rast_open_old(name, mapset);

    /* controlling, if we can open input raster */
    Rast_get_cellhd(name, mapset, &cell_head);

    G_debug(3, "number of rows %d", cell_head.rows);

    /* Allocate input buffer */
    input_raster = Rast_allocate_buf(data_type);

    /* Allocate output buffer, use input map data_type */
    nrows = Rast_window_rows();
    ncols = Rast_window_cols();
    output_raster = Rast_allocate_buf(data_type);

    /* controlling, if we can write the raster */
    output_fd = Rast_open_new(result, data_type);

    /* for each row */
    for (row = 0; row < nrows; row++) {
        CELL c;
        FCELL f;
        DCELL d;

        G_percent(row, nrows, 2);

        /* read input map */
        Rast_get_row(input_fd, input_raster, row, data_type);

        /* process the data */
        for (col = 0; col < ncols; col++) {
            /* use different function for each data type */
            switch (data_type) {
            case CELL_TYPE:
                c = ((CELL *) input_raster)[col];
                c = times_two(c);  /* calculate */
                ((CELL *) output_raster)[col] = c;
                break;
            case FCELL_TYPE:
                f = ((FCELL *) input_raster)[col];
                f = times_two(f);  /* calculate */
                ((FCELL *) output_raster)[col] = f;
                break;
            case DCELL_TYPE:
                d = ((DCELL *) input_raster)[col];
                d = times_two(d);  /* calculate */
                ((DCELL *) output_raster)[col] = d;
                break;
            }
        }

        /* write raster row to output raster map */
        Rast_put_row(output_fd, output_raster, data_type);
    }

    /* memory cleanup */
    G_free(input_raster);
    G_free(output_raster);

    /* closing raster maps */
    Rast_close(input_fd);
    Rast_close(output_fd);

    /* add command line incantation to history file */
    Rast_short_history(result, "raster", &history);
    Rast_command_history(&history);
    Rast_write_history(result, &history);


    exit(EXIT_SUCCESS);
}
