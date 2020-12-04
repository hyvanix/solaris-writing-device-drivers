#include <sys/devops.h>  /* used by dev_ops */
#include <sys/conf.h>    /* used by dev_ops and cb_ops */
#include <sys/modctl.h>  /* used by modlinkage, modldrv, _init, _info, */
                         /* and _fini */
#include <sys/cmn_err.h> /* used by all entry points for this driver */
#include <sys/ddi.h>     /* used by all entry points for this driver */
                         /* also used by cb_ops, ddi_get_instance, and */
                         /* ddi_prop_op */
#include <sys/sunddi.h>  /* used by all entry points for this driver */
                         /* also used by cb_ops, ddi_create_minor_node, */
                         /* ddi_get_instance, and ddi_prop_op */

#define QOTD_MAXLEN	128

static const char qotd[QOTD_MAXLEN]
	= "Be careful about reading health books. \
You may die from a misprint. - Mark Twain\n";

/* dev_ops structure */
static struct dev_ops qotd_dev_ops = {
    DEVO_REV,                  /* devo_rev */
    0,                         /* reference count */
    ddi_no_info,               /* no getinfo(9E) */
    nulldev,                   /* no identify(9E) - nulldev returns 0 */
    nulldev,                   /* no probe(9E) */
    nulldev,                   /* devo_attach */
    nulldev,                   /* devo_dettach */
    nodev,                     /* no reset - nodev returns ENXIO */
    (struct cb_ops *)NULL,     /* devo_cb_ops */
    (struct bus_ops *)NULL,    /* devo_bus_ops */
    nodev                     /* no power(9E) */
};

/* modldrv structure */
static struct modldrv modldrv = {
    &mod_driverops,             /* Type of module. This is a driver. */
    "Quote of the Day 1.0",     /* Name of the module. */
    &qotd_dev_ops
};

/* modlinkage structure */
static struct modlinkage modlinkage = {
    MODREV_1,
    (void *)&modldrv,
    NULL
};

/* Loadable module configuration entry points */
int
_init(void)
{
    cmn_err(CE_CONT, "QOTD: %s\n", qotd);
    return(mod_install(&modlinkage));
}

int
_info(struct modinfo *modinfop)
{
    return(mod_info(&modlinkage, modinfop));
}

int
_fini(void)
{
    return(mod_remove(&modlinkage));
}
