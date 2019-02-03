/**
 * Author: Hou Wang
 *
 * Description: This file defines the file data block in archive
 */

#include "ArchiveFileBlock.hpp"

namespace filestorage {
        std::istream& operator>>(std::istream& in, FileBlock& obj) {
            obj.read(in);
            return in;
        }

        std::ostream& operator<<(std::ostream& out, const FileBlock& obj) {
            obj.write(out);
            return out;
        }

        void FileBlock::read(std::istream& in) {
            in.read(this->block, BLOCK_SIZE * sizeof(byte));
        }

        void FileBlock::write(std::ostream& out) const {
            out.write(this->block, BLOCK_SIZE * sizeof(byte));
        }
}