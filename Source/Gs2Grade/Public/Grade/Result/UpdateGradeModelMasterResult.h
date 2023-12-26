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
#include "../Model/GradeModelMaster.h"

namespace Gs2::Grade::Result
{
    class GS2GRADE_API FUpdateGradeModelMasterResult final : public TSharedFromThis<FUpdateGradeModelMasterResult>
    {
        TSharedPtr<Model::FGradeModelMaster> ItemValue;
        
    public:
        
        FUpdateGradeModelMasterResult();
        FUpdateGradeModelMasterResult(
            const FUpdateGradeModelMasterResult& From
        );
        ~FUpdateGradeModelMasterResult() = default;

        TSharedPtr<FUpdateGradeModelMasterResult> WithItem(const TSharedPtr<Model::FGradeModelMaster> Item);

        TSharedPtr<Model::FGradeModelMaster> GetItem() const;

        static TSharedPtr<FUpdateGradeModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateGradeModelMasterResult, ESPMode::ThreadSafe> FUpdateGradeModelMasterResultPtr;
}