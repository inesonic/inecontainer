/*-*-c++-*-*************************************************************************************************************
* Copyright 2016 - 2022 Inesonic, LLC.
*
* MIT License:
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
*   documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
*   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
*   permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
*   Software.
*   
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
*   WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
*   OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
*   OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
********************************************************************************************************************//**
* \file
*
* This header defines the \ref Container::MemoryContainer::Private class.
***********************************************************************************************************************/

/* .. sphinx-project inecontainer */

#ifndef CONTAINER_MEMORY_CONTAINER_PRIVATE_H
#define CONTAINER_MEMORY_CONTAINER_PRIVATE_H

#include <cstdint>
#include <vector>
#include <map>
#include <string>

#include "container_status.h"
#include "container_memory_container.h"

namespace Container {
    /**
     * Private implementation of the \ref MemoryContainer class.
     */
    class MemoryContainer::Private {
        public:
            /**
             * Constructor
             *
             * \param[in] interface Pointer to the interface class instance.
             */
            Private(MemoryContainer* interface);

            ~Private();

            /**
             * Method that sets the memory buffer to be used for the container.
             *
             * \param[in] newBuffer Pointer to the memory buffer.
             */
            void setBuffer(std::shared_ptr<MemoryContainer::MemoryBuffer> newBuffer);

            /**
             * Method you can use to obtain access to the raw buffer being used by this class.
             *
             * \return Returns a shared pointer to the underlying buffer.
             */
            std::shared_ptr<MemoryContainer::MemoryBuffer> buffer();

            /**
             * Method that is called to determine the current size of the underlying data store, in bytes.
             *
             * \return Returns the size of the underlying data store, in bytes.  A negative value should be returned if
             *         an error occurs.
             */
            long long size();

            /**
             * Method that is called to seek to a position in the underlying data store prior to performing a call to
             * \ref Container::Container::read, \ref Container::Container::write, or
             * \ref Container::Container::truncate.
             *
             * \param[in] newOffset The new position in the underlying data store to seek to.
             *
             * \return Returns the status from this operation.
             */
            Status setPosition(unsigned long long newOffset);

            /**
             * Method that is called to seek to the last just past the last byte in the underlying data store.
             *
             * \return Returns the status from this operation.
             */
            Status setPositionLast();

            /**
             * Method that is called to determine the current byte offset from the beginning of the container.
             *
             * \return Returns the current byte offset from the beginning of the container.
             */
            unsigned long long position() const;

            /**
             * Method that is called to read a specified number of bytes of data from the underlying data store.
             *
             * \param[in] buffer       The buffer to receive the data.  The buffer is guaranteed to be large enough to
             *                         hold all the requested data.
             *
             * \param[in] desiredCount The number of bytes that are expected to be read.
             *
             * \return Returns the status from the read operation.  An instance of \ref Container::ReadSuccessful should
             *         be returned on success.
             */
            Status read(std::uint8_t* buffer, unsigned desiredCount);

            /**
             * Method that is called to write a specified number of bytes of data to the underlying data store.
             *
             * \param[in] buffer The buffer holding the data to be written.
             *
             * \param[in] count  The number of bytes to be written.
             *
             * \return Returns the status from the write operation.  An instance of \ref Container::WriteSuccessful
             *         should be returned on success.
             */
            Status write(const std::uint8_t* buffer, unsigned count);

            /**
             * Method you can overload to indicate whether the derived class supports file truncation.
             *
             * \return Returns true if file truncation is supported.  Returns false if file truncation is not supported.
             */
            bool supportsTruncation() const;

            /**
             * Method that is called to truncate the container at the current file position.
             *
             * \return Returns the status from the truncate operation.
             */
            Status truncate();

            /**
             * Method that is called to force any written data to be flushed to the media.
             *
             * \return Returns the status from the flush operation.
             */
            Status flush();

        private:
            /**
             * Pointer to the memory container class instance.
             */
            MemoryContainer* iface;

            /**
             * Pointer to the memory buffer.
             */
            std::shared_ptr<MemoryContainer::MemoryBuffer> memoryBuffer;

            /**
             * Pointer to the memory buffer position.
             */
            unsigned long long currentPosition;
    };
}

#endif