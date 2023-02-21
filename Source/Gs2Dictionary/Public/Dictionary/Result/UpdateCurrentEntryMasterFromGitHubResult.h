/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "../Model/CurrentEntryMaster.h"

namespace Gs2::Dictionary::Result
{
    class GS2DICTIONARY_API FUpdateCurrentEntryMasterFromGitHubResult final : public TSharedFromThis<FUpdateCurrentEntryMasterFromGitHubResult>
    {
        TSharedPtr<Model::FCurrentEntryMaster> ItemValue;
        
    public:
        
        FUpdateCurrentEntryMasterFromGitHubResult();
        FUpdateCurrentEntryMasterFromGitHubResult(
            const FUpdateCurrentEntryMasterFromGitHubResult& From
        );
        ~FUpdateCurrentEntryMasterFromGitHubResult() = default;

        TSharedPtr<FUpdateCurrentEntryMasterFromGitHubResult> WithItem(const TSharedPtr<Model::FCurrentEntryMaster> Item);

        TSharedPtr<Model::FCurrentEntryMaster> GetItem() const;

        static TSharedPtr<FUpdateCurrentEntryMasterFromGitHubResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentEntryMasterFromGitHubResult, ESPMode::ThreadSafe> FUpdateCurrentEntryMasterFromGitHubResultPtr;
}