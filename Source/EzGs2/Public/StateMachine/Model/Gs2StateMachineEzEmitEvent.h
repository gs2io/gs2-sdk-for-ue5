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
#include "StateMachine/Model/EmitEvent.h"

namespace Gs2::UE5::StateMachine::Model
{
	class EZGS2_API FEzEmitEvent final : public TSharedFromThis<FEzEmitEvent>
	{
        TOptional<FString> EventValue;
        TOptional<FString> ParametersValue;
        TOptional<int64> TimestampValue;

	public:
        TSharedPtr<FEzEmitEvent> WithEvent(const TOptional<FString> Event);
        TSharedPtr<FEzEmitEvent> WithParameters(const TOptional<FString> Parameters);
        TSharedPtr<FEzEmitEvent> WithTimestamp(const TOptional<int64> Timestamp);

        TOptional<FString> GetEvent() const;

        TOptional<FString> GetParameters() const;

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;

        Gs2::StateMachine::Model::FEmitEventPtr ToModel() const;
        static TSharedPtr<FEzEmitEvent> FromModel(Gs2::StateMachine::Model::FEmitEventPtr Model);
    };
    typedef TSharedPtr<FEzEmitEvent> FEzEmitEventPtr;
}