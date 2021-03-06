// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFAPI_RENDER_CPDF_IMAGECACHEENTRY_H_
#define CORE_FPDFAPI_RENDER_CPDF_IMAGECACHEENTRY_H_

#include <stdint.h>

#include "core/fpdfapi/page/cpdf_dib.h"
#include "core/fxcrt/retain_ptr.h"
#include "core/fxcrt/unowned_ptr.h"

class CPDF_Dictionary;
class CPDF_Document;
class CPDF_Image;
class CPDF_RenderStatus;
class PauseIndicatorIface;

class CPDF_ImageCacheEntry {
 public:
  CPDF_ImageCacheEntry(CPDF_Document* pDoc,
                       const RetainPtr<CPDF_Image>& pImage);
  ~CPDF_ImageCacheEntry();

  void Reset();
  uint32_t EstimateSize() const { return m_dwCacheSize; }
  uint32_t GetMatteColor() const { return m_MatteColor; }
  uint32_t GetTimeCount() const { return m_dwTimeCount; }
  void SetTimeCount(uint32_t count) { m_dwTimeCount = count; }
  CPDF_Image* GetImage() const { return m_pImage.Get(); }

  CPDF_DIB::LoadState StartGetCachedBitmap(
      const CPDF_Dictionary* pPageResources,
      const CPDF_RenderStatus* pRenderStatus,
      bool bStdCS);

  // Returns whether to Continue() or not.
  bool Continue(PauseIndicatorIface* pPause, CPDF_RenderStatus* pRenderStatus);

  RetainPtr<CFX_DIBBase> DetachBitmap();
  RetainPtr<CFX_DIBBase> DetachMask();

 private:
  void ContinueGetCachedBitmap(const CPDF_RenderStatus* pRenderStatus);
  void CalcSize();

  uint32_t m_dwTimeCount = 0;
  uint32_t m_MatteColor = 0;
  uint32_t m_dwCacheSize = 0;
  UnownedPtr<CPDF_Document> const m_pDocument;
  RetainPtr<CPDF_Image> const m_pImage;
  RetainPtr<CFX_DIBBase> m_pCurBitmap;
  RetainPtr<CFX_DIBBase> m_pCurMask;
  RetainPtr<CFX_DIBBase> m_pCachedBitmap;
  RetainPtr<CFX_DIBBase> m_pCachedMask;
};

#endif  // CORE_FPDFAPI_RENDER_CPDF_IMAGECACHEENTRY_H_
