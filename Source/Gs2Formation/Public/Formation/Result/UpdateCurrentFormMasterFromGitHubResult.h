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
#include "../Model/CurrentFormMaster.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FUpdateCurrentFormMasterFromGitHubResult final : public TSharedFromThis<FUpdateCurrentFormMasterFromGitHubResult>
    {
        TSharedPtr<Model::FCurrentFormMaster> ItemValue;
        
    public:
        
        FUpdateCurrentFormMasterFromGitHubResult();
        FUpdateCurrentFormMasterFromGitHubResult(
            const FUpdateCurrentFormMasterFromGitHubResult& From
        );
        ~FUpdateCurrentFormMasterFromGitHubResult() = default;

        TSharedPtr<FUpdateCurrentFormMasterFromGitHubResult> WithItem(const TSharedPtr<Model::FCurrentFormMaster> Item);

        TSharedPtr<Model::FCurrentFormMaster> GetItem() const;

        static TSharedPtr<FUpdateCurrentFormMasterFromGitHubResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentFormMasterFromGitHubResult, ESPMode::ThreadSafe> FUpdateCurrentFormMasterFromGitHubResultPtr;
}