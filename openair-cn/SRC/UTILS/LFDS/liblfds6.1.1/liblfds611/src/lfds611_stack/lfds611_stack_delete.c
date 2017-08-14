/*
 * Copyright (c) 2015, EURECOM (www.eurecom.fr)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
 */

#include "lfds611_stack_internal.h"/****************************************************************************/voidlfds611_stack_delete (  struct lfds611_stack_state *ss,  void                                    (*user_data_delete_function) (void *user_data,      void *user_state),  void *user_state) {  void  *user_data;  assert (ss != NULL);     // TRD : user_data_delete_function can be NULL  // TRD : user_state can be NULL  while (lfds611_stack_pop (ss, &user_data))    if (user_data_delete_function != NULL)      user_data_delete_function (user_data, user_state);  lfds611_freelist_delete (ss->fs, lfds611_stack_internal_freelist_delete_function, NULL);  lfds611_liblfds_aligned_free (ss);  return;}/****************************************************************************/voidlfds611_stack_clear (  struct lfds611_stack_state *ss,  void                                    (*user_data_clear_function) (void *user_data,      void *user_state),  void *user_state) {  void  *user_data;  assert (ss != NULL);  // TRD : user_data_clear_function can be NULL  // TRD : user_state can be NULL  while (lfds611_stack_pop (ss, &user_data))    if (user_data_clear_function != NULL)      user_data_clear_function (user_data, user_state);  return;}/****************************************************************************///#pragma warning( disable : 4100 )voidlfds611_stack_internal_freelist_delete_function (  void *user_data,  void *user_state) {  assert (user_data != NULL);  assert (user_state == NULL);  lfds611_liblfds_aligned_free (user_data);  return;}//#pragma warning( default : 4100 )
