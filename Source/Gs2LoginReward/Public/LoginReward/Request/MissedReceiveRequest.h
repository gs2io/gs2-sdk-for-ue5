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
#include "../Model/Config.h"

namespace Gs2::LoginReward::Request
{
    class FMissedReceiveRequest;

    class GS2LOGINREWARD_API FMissedReceiveRequest final : public TSharedFromThis<FMissedReceiveRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> StepNumberValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FMissedReceiveRequest();
        FMissedReceiveRequest(
            const FMissedReceiveRequest& From
        );
        ~FMissedReceiveRequest() = default;

        TSharedPtr<FMissedReceiveRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FMissedReceiveRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FMissedReceiveRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FMissedReceiveRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FMissedReceiveRequest> WithStepNumber(const TOptional<int32> StepNumber);
        TSharedPtr<FMissedReceiveRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FMissedReceiveRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetStepNumber() const;
        FString GetStepNumberString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FMissedReceiveRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMissedReceiveRequest, ESPMode::ThreadSafe> FMissedReceiveRequestPtr;
}