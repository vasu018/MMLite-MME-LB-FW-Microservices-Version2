/*********************************************************************
 *                     openNetVM
 *              https://sdnfv.github.io
 *
 *   BSD LICENSE
 *
 *   Copyright(c)
 *            2015-2016 George Washington University
 *            2015-2016 University of California Riverside
 *            2016 Hewlett Packard Enterprise Development LP
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * The name of the author may not be used to endorse or promote
 *       products derived from this software without specific prior
 *       written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ********************************************************************/


/******************************************************************************

                                onvm_nflib.h


                           Header file for the API


******************************************************************************/


#ifndef _ONVM_NFLIB_H_
#define _ONVM_NFLIB_H_
#include <rte_mbuf.h>
#include "onvm_common.h"
//#ifdef INTERRUPT_SEM  //move maro to makefile, otherwise uncomemnt or need to include these after including common.h
#include <rte_cycles.h>
//#endif

/************************************API**************************************/

extern char *client_name_extern;
/**
 * Initialize the OpenNetVM container Library.
 * This will setup the DPDK EAL as a secondary process, and notify the host
 * that there is a new NF.
 *
 * @argc
 *   The argc argument that was given to the main() function.
 * @argv
 *   The argv argument that was given to the main() function
 * @param tag
 *   A uniquely identifiable string for this NF.
 *   For example, can be the application name (e.g. "bridge_nf")
 * @return
 *   On success, the number of parsed arguments, which is greater or equal to
 *   zero. After the call to onvm_nf_init(), all arguments argv[x] with x < ret
 *   may be modified and should not be accessed by the application.,
 *   On error, a negative value .
 */
int
onvm_nflib_init(int argc, char *argv[], const char *nf_tag);


/**
 * Run the OpenNetVM container Library.
 * This will register the callback used for each new packet. It will then
 * loop forever waiting for packets.
 *
 * @param info
 *   an info struct describing this NF app. Must be from a huge page memzone.
 * @param handler
 *   a pointer to the function that will be called on each received packet.
 * @return
 *   0 on success, or a negative value on error.
 */
int
onvm_nflib_run(struct onvm_nf_info* info, int(*handler)(struct rte_mbuf* pkt, struct onvm_pkt_meta* action));


/**
 * Return a packet that has previously had the ONVM_NF_ACTION_BUFFER action
 * called on it.
 *
 * @param pkt
 *    a pointer to a packet that should now have a action other than buffer.
 * @return
 *    0 on success, or a negative value on error.
 */
int
onvm_nflib_return_pkt(struct rte_mbuf* pkt);

/**
 * Process an message. Does stuff.
 *
 * @param msg
 *    a pointer to a message to be processed
 * @return
 *    0 on success, or a negative value on error
 */
int
onvm_nflib_handle_msg(struct onvm_nf_msg *msg);

/**
 * Stop this NF and clean up its memory
 * Sends shutdown message to manager.
 */
void
onvm_nflib_stop(void);

/**
 * Return the tx_ring associated with this NF.
 *
 * @param info
 *   an info struct describing this NF app.
 * @return
 *    pointer to tx_ring structure associated with info, NULL on error.
 */
struct rte_ring *
onvm_nflib_get_tx_ring(struct onvm_nf_info* info);


/**
 * Return the rx_ring associated with this NF.
 *
 * @param info
 *   an info struct describing this NF app.
 * @return
 *    pointer to rx_ring structure associated with info, NULL on error.
 */
struct rte_ring *
onvm_nflib_get_rx_ring(struct onvm_nf_info* info);


/**
 * Return the tx_stats associated with this NF.
 *
 * @param info
 *   an info struct describing this NF app.
 * @return
 *    pointer to tx_stats structure associated with info, NULL on error.
 */
volatile struct client_tx_stats *
onvm_nflib_get_tx_stats(struct onvm_nf_info* info);

int
onvm_nflib_parse_args(int argc, char *argv[]);

#endif  // _ONVM_NFLIB_H_
