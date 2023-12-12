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
#include "StateMachine/Model/ChangeStateEvent.h"

namespace Gs2::UE5::StateMachine::Model
{
	class EZGS2_API FEzChangeStateEvent final : public TSharedFromThis<FEzChangeStateEvent>
	{
        TOptional<FString> TaskNameValue;
        TOptional<FString> HashValue;
        TOptional<int64> TimestampValue;

	public:
        TSharedPtr<FEzChangeStateEvent> WithTaskName(const TOptional<FString> TaskName);
        TSharedPtr<FEzChangeStateEvent> WithHash(const TOptional<FString> Hash);
        TSharedPtr<FEzChangeStateEvent> WithTimestamp(const TOptional<int64> Timestamp);

        TOptional<FString> GetTaskName() const;

        TOptional<FString> GetHash() const;

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;

        Gs2::StateMachine::Model::FChangeStateEventPtr ToModel() const;
        static TSharedPtr<FEzChangeStateEvent> FromModel(Gs2::StateMachine::Model::FChangeStateEventPtr Model);
    };
    typedef TSharedPtr<FEzChangeStateEvent> FEzChangeStateEventPtr;
}