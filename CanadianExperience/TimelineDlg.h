/**
 * \file TimelineDlg.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * CTimeline dialog
 */

#pragma once

class CTimeline;


/**
 * CTimeline dialog
 */
class CTimelineDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimelineDlg)

public:
	CTimelineDlg(CWnd* pParent = nullptr);
	virtual ~CTimelineDlg();

	void SetTimeline(CTimeline * timeline);

	void Take();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMELINEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	/// variable that holds the input from the dialog box
	int mNumFrames;

	/// The timeline we are editing
	CTimeline *mTimeline = nullptr;
	int mFrameRate;			///< The framerate of the animation
};
