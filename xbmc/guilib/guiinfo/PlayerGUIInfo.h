/*
 *  Copyright (C) 2012-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/guiinfo/GUIInfoProvider.h"
#include "utils/EventStream.h"
#include "utils/TimeFormat.h"

#include <atomic>
#include <ctime>
#include <memory>
#include <utility>
#include <vector>

class CDataCacheCore;

namespace KODI
{
namespace GUILIB
{
namespace GUIINFO
{

class CGUIInfo;

struct PlayerShowInfoChangedEvent
{
  explicit PlayerShowInfoChangedEvent(bool showInfo) : m_showInfo(showInfo) {}
  virtual ~PlayerShowInfoChangedEvent() = default;

  bool m_showInfo{false};
};

class CPlayerGUIInfo : public CGUIInfoProvider
{
public:
  CPlayerGUIInfo();
  ~CPlayerGUIInfo() override;

  CEventStream<PlayerShowInfoChangedEvent>& Events() { return m_events; }

  // KODI::GUILIB::GUIINFO::IGUIInfoProvider implementation
  bool InitCurrentItem(CFileItem *item) override;
  bool GetLabel(std::string& value, const CFileItem *item, int contextWindow, const CGUIInfo &info, std::string *fallback) const override;
  bool GetInt(int& value, const CGUIListItem *item, int contextWindow, const CGUIInfo &info) const override;
  bool GetBool(bool& value, const CGUIListItem *item, int contextWindow, const CGUIInfo &info) const override;

  void SetShowTime(bool showtime) { m_playerShowTime = showtime; }
  void SetShowInfo(bool showinfo);
  bool GetShowInfo() const { return m_playerShowInfo; }
  bool ToggleShowInfo();

private:
  std::unique_ptr<CFileItem> m_currentItem;

  std::atomic_bool m_playerShowTime;
  std::atomic_bool m_playerShowInfo;

  int GetTotalPlayTime() const;
  int GetPlayTime() const;
  int GetPlayTimeRemaining() const;
  float GetSeekPercent() const;

  CEventSource<PlayerShowInfoChangedEvent> m_events;

  std::string GetCurrentPlayTime(TIME_FORMAT format) const;
  std::string GetCurrentPlayTimeRemaining(TIME_FORMAT format) const;
  std::string GetDuration(TIME_FORMAT format) const;
  std::string GetCurrentSeekTime(TIME_FORMAT format) const;
  std::string GetSeekTime(TIME_FORMAT format) const;

  std::string GetContentRanges(int iInfo) const;
  std::vector<std::pair<float, float>> GetEditList(const CDataCacheCore& data,
                                                   std::time_t duration) const;
  std::vector<std::pair<float, float>> GetCuts(const CDataCacheCore& data,
                                               std::time_t duration) const;
  std::vector<std::pair<float, float>> GetSceneMarkers(const CDataCacheCore& data,
                                                       std::time_t duration) const;
  std::vector<std::pair<float, float>> GetChapters(const CDataCacheCore& data,
                                                   std::time_t duration) const;
};

} // namespace GUIINFO
} // namespace GUILIB
} // namespace KODI
