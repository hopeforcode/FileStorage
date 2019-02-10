/**
 * Author: Hou Wang
 *
 * Description: This file defines the file data block in archive
 */

#include "ArchiveFileBuffer.hpp"
#include <algorithm>

namespace filestorage {
        std::istream& operator>>(std::istream& in, FileBuffer& obj) {
            obj.read(in);
            return in;
        }

        std::ostream& operator<<(std::ostream& out, FileBuffer& obj) {
            obj.write(out);
            return out;
        }

        void FileBuffer::read(std::istream& in, unsigned int bytes) {
            in.read(this->block, bytes * sizeof(byte));
            int count = in.gcount();
            this->size = count < bytes ? count : bytes;
        }

        void FileBuffer::read(std::istream& in) {
            this->read(in, BLOCK_SIZE);
        }

        void FileBuffer::write(std::ostream& out) {
            out.write(this->block, this->size * sizeof(byte));
            this->size = 0;
            this->reset();
        }

        void FileBuffer::reset() {
            std::fill(this->block, this->block + BLOCK_SIZE, 0);
        }
}