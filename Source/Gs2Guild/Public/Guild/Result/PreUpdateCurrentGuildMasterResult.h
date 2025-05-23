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

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FPreUpdateCurrentGuildMasterResult final : public TSharedFromThis<FPreUpdateCurrentGuildMasterResult>
    {
        TOptional<FString> UploadTokenValue;
        TOptional<FString> UploadUrlValue;
        
    public:
        
        FPreUpdateCurrentGuildMasterResult();
        FPreUpdateCurrentGuildMasterResult(
            const FPreUpdateCurrentGuildMasterResult& From
        );
        ~FPreUpdateCurrentGuildMasterResult() = default;

        TSharedPtr<FPreUpdateCurrentGuildMasterResult> WithUploadToken(const TOptional<FString> UploadToken);
        TSharedPtr<FPreUpdateCurrentGuildMasterResult> WithUploadUrl(const TOptional<FString> UploadUrl);

        TOptional<FString> GetUploadToken() const;
        TOptional<FString> GetUploadUrl() const;

        static TSharedPtr<FPreUpdateCurrentGuildMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPreUpdateCurrentGuildMasterResult, ESPMode::ThreadSafe> FPreUpdateCurrentGuildMasterResultPtr;
}