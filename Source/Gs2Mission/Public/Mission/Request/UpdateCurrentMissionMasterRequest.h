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

namespace Gs2::Mission::Request
{
    class FUpdateCurrentMissionMasterRequest;

    class GS2MISSION_API FUpdateCurrentMissionMasterRequest final : public TSharedFromThis<FUpdateCurrentMissionMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ModeValue;
        TOptional<FString> SettingsValue;
        TOptional<FString> UploadTokenValue;
        
    public:
        
        FUpdateCurrentMissionMasterRequest();
        FUpdateCurrentMissionMasterRequest(
            const FUpdateCurrentMissionMasterRequest& From
        );
        ~FUpdateCurrentMissionMasterRequest() = default;

        TSharedPtr<FUpdateCurrentMissionMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentMissionMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentMissionMasterRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FUpdateCurrentMissionMasterRequest> WithSettings(const TOptional<FString> Settings);
        TSharedPtr<FUpdateCurrentMissionMasterRequest> WithUploadToken(const TOptional<FString> UploadToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetSettings() const;
        TOptional<FString> GetUploadToken() const;

        static TSharedPtr<FUpdateCurrentMissionMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentMissionMasterRequest> FUpdateCurrentMissionMasterRequestPtr;
}