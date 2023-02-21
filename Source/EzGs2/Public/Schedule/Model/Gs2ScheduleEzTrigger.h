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
#include "Schedule/Model/Trigger.h"

namespace Gs2::UE5::Schedule::Model
{
	class EZGS2_API FEzTrigger final : public TSharedFromThis<FEzTrigger>
	{
        TOptional<FString> TriggerIdValue;
        TOptional<FString> NameValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> ExpiresAtValue;

	public:
        TSharedPtr<FEzTrigger> WithTriggerId(const TOptional<FString> TriggerId);
        TSharedPtr<FEzTrigger> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzTrigger> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEzTrigger> WithExpiresAt(const TOptional<int64> ExpiresAt);

        TOptional<FString> GetTriggerId() const;

        TOptional<FString> GetName() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        Gs2::Schedule::Model::FTriggerPtr ToModel() const;
        static TSharedPtr<FEzTrigger> FromModel(Gs2::Schedule::Model::FTriggerPtr Model);
    };
    typedef TSharedPtr<FEzTrigger> FEzTriggerPtr;
}