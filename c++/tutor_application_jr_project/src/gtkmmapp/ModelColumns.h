#ifndef MODELCOLUMNS_H_
#define MODELCOLUMNS_H_

class ModelColumns : public TreeModel::ColumnRecord
{
public:
	ModelColumns()
	{
		this->add(m_col_id);
		this->add(m_col_name);
		this->add(m_col_subject);
		this->add(m_col_time);
	}
	~ModelColumns()
	{
	}
	Gtk::TreeModelColumn<unsigned int> m_col_id;
	Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	Gtk::TreeModelColumn<Glib::ustring> m_col_subject;
	Gtk::TreeModelColumn<int> m_col_time;
};

#endif // MODELCOLUMNS_H_
