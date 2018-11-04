#pragma once

class config
{
	size_t begin; //��������� �������
	size_t end; //�������� �������
	bool on; //������� ���������� ��� ����������� ����� (begin, end) �� ������������
	size_t cost; //������ ������ ������� ������������, �.�. ������ ���� ������ ������ ������������ ( �������� ) ������ �� �����
	bool checked;
public:
	config( size_t _begin, size_t _end, bool _on, size_t _cost );
	config( void ) { begin = 0; end = 0; on = 0; cost = 0; checked = 0;  }
	
	void check( void ) { checked = true; } // ������������ ������������, �� ������ �������
	friend class SolutionTree;
	friend class matrix;
};
