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
#include "Dom/JsonObject.h"
#include "../Model/Config.h"

namespace Gs2::LoginReward::Request
{
    class FMissedReceiveByUserIdRequest;

    class GS2LOGINREWARD_API FMissedReceiveByUserIdRequest final : public TSharedFromThis<FMissedReceiveByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> StepNumberValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FMissedReceiveByUserIdRequest();
        FMissedReceiveByUserIdRequest(
            const FMissedReceiveByUserIdRequest& From
        );
        ~FMissedReceiveByUserIdRequest() = default;

        TSharedPtr<FMissedReceiveByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FMissedReceiveByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FMissedReceiveByUserIdRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FMissedReceiveByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMissedReceiveByUserIdRequest> WithStepNumber(const TOptional<int32> StepNumber);
        TSharedPtr<FMissedReceiveByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FMissedReceiveByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FMissedReceiveByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetStepNumber() const;
        FString GetStepNumberString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FMissedReceiveByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMissedReceiveByUserIdRequest> FMissedReceiveByUserIdRequestPtr;
}