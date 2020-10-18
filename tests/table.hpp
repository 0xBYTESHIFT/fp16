#pragma once

//original by @haaruba on github/haaruba/cpp-text-table under GPL2.1
//rewritten by 0xBYTESHIFT for github/0xBYTESHIFT/fp16

#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>

class cli_table {
public:
    enum class alignment_t { left, right }; 
    using row = std::vector<std::string>;

    cli_table(char horizontal='-', char vertical='|', char corner='+', bool ruller=true)
        :m_horizontal(horizontal),
        m_vertical(vertical),
        m_corner(corner),
        m_has_ruler(ruller)
    {}

    void set_alignment(unsigned i, alignment_t a) {
        m_alignment[i] = a;
    }

    alignment_t alignment(unsigned i)const {
        return m_alignment.at(i);
    }
    char vertical()const {
        return m_vertical;
    }
    char horizontal()const {
        return m_horizontal;
    }

    void add(const std::string &content) {
        m_current.emplace_back(content);
    }
    void end_of_row() {
        m_rows.emplace_back(m_current);
        m_current.assign(0, "");
    }

    template<class It>
    void add_row(It begin, It end) {
        for(auto i = begin; i != end; ++i) {
           add(*i); 
        }
        end_of_row();
    }

    template<class Cont>
    void add_row(const Cont &container) {
        add_row(container.begin(), container.end());
    }

    const std::vector<row>& rows()const {
        return m_rows;
    }

    void setup()const {
        determine_widths();
        setup_alignment();
    }

    std::string ruler()const {
        std::string result;
        result += m_corner;
        for(auto width = m_width.begin(); width != m_width.end(); ++width) {
            result += std::string(*width, m_horizontal);
            result += m_corner;
        }

        return result;
    }

    int width(unsigned i)const {
        return m_width.at(i);
    }

	bool has_ruler()const {
        return m_has_ruler;
    }

	long correct_distance(const std::string &string_to_correct)const {
        auto len = static_cast<long>(glyph_len(string_to_correct));
        return static_cast<long>(string_to_correct.size()) - len;
    };
	
private:
    const char m_horizontal;
    const char m_vertical;
    const char m_corner;
    const bool m_has_ruler;
    row m_current;
    std::vector<row> m_rows;
    std::vector<unsigned> mutable m_width;
	std::vector<unsigned> mutable m_utf8width;
    std::map<unsigned, alignment_t> mutable m_alignment;

    unsigned columns()const {
        return m_rows.at(0).size();
    }

	unsigned glyph_len(const std::string &s)const {
		unsigned int _byteLength = s.length();
		return _byteLength;
	}
	
    void determine_widths()const {
        m_width.assign(columns(), 0);
		m_utf8width.assign(columns(), 0);
        for(auto row_it = m_rows.begin(); row_it != m_rows.end(); ++row_it) {
            const auto& row = *row_it;
            for(unsigned i = 0; i < row.size(); ++i) {
                auto &w_at = m_width.at(i);
                w_at = w_at > glyph_len(row.at(i))? w_at : glyph_len(row.at(i));
            }
        }
    }

    void setup_alignment()const {
        for(unsigned i = 0; i < columns(); ++i) {
            if (m_alignment.find(i) == m_alignment.end()) {
                m_alignment.emplace(i, alignment_t::left);
            }
        }
    }
};

inline std::ostream & operator<<( std::ostream & stream, const cli_table &table) {
    table.setup();
	if (table.has_ruler()) {
	    stream << table.ruler() << "\n";
	}
    for (auto row_it = table.rows().begin(); row_it != table.rows().end(); ++row_it) {
        const auto& row = *row_it;
        stream << table.vertical();
        for (unsigned i = 0; i < row.size(); ++i) {
            auto alignment = table.alignment(i) == cli_table::alignment_t::left? std::left : std::right;
			// std::setw( width ) works as follows: a string which goes in the stream with byte length (!) l is filled with n spaces so that l+n=width.
			// For a utf8 encoded string the glyph length g might be smaller than l. We need n spaces so that g+n=width which is equivalent to g+n+l-l=width ==> l+n = width+l-g
			// l-g (that means glyph length minus byte length) has to be added to the width argument.
			// l-g is computed by correctDistance. 
            const auto &row_i = row.at(i);
            auto w = table.width(i) + table.correct_distance(row_i);
            stream << std::setw(w) << alignment << row_i;
            stream << table.vertical();
        }
        stream << "\n";
		if (table.has_ruler()) {
        	stream << table.ruler() << "\n";
		}
    }

    return stream;
}