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
#include "JobQueue/Model/JobResultBody.h"

namespace Gs2::UE5::JobQueue::Model
{
	class EZGS2_API FEzJobResultBody final : public TSharedFromThis<FEzJobResultBody>
	{
        TOptional<int32> TryNumberValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ResultValue;
        TOptional<int64> TryAtValue;

	public:
        TSharedPtr<FEzJobResultBody> WithTryNumber(const TOptional<int32> TryNumber);
        TSharedPtr<FEzJobResultBody> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FEzJobResultBody> WithResult(const TOptional<FString> Result);
        TSharedPtr<FEzJobResultBody> WithTryAt(const TOptional<int64> TryAt);

        TOptional<int32> GetTryNumber() const;
        FString GetTryNumberString() const;

        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;

        TOptional<FString> GetResult() const;

        TOptional<int64> GetTryAt() const;
        FString GetTryAtString() const;

        Gs2::JobQueue::Model::FJobResultBodyPtr ToModel() const;
        static TSharedPtr<FEzJobResultBody> FromModel(Gs2::JobQueue::Model::FJobResultBodyPtr Model);
    };
    typedef TSharedPtr<FEzJobResultBody> FEzJobResultBodyPtr;
}