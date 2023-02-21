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
#include "JobQueue/Model/JobResult.h"

namespace Gs2::UE5::JobQueue::Model
{
	class EZGS2_API FEzJobResult final : public TSharedFromThis<FEzJobResult>
	{
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ResultValue;

	public:
        TSharedPtr<FEzJobResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FEzJobResult> WithResult(const TOptional<FString> Result);

        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;

        TOptional<FString> GetResult() const;

        Gs2::JobQueue::Model::FJobResultPtr ToModel() const;
        static TSharedPtr<FEzJobResult> FromModel(Gs2::JobQueue::Model::FJobResultPtr Model);
    };
    typedef TSharedPtr<FEzJobResult> FEzJobResultPtr;
}