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

namespace Gs2::MegaField::Result
{
    class GS2MEGAFIELD_API FPreUpdateCurrentFieldMasterResult final : public TSharedFromThis<FPreUpdateCurrentFieldMasterResult>
    {
        TOptional<FString> UploadTokenValue;
        TOptional<FString> UploadUrlValue;
        
    public:
        
        FPreUpdateCurrentFieldMasterResult();
        FPreUpdateCurrentFieldMasterResult(
            const FPreUpdateCurrentFieldMasterResult& From
        );
        ~FPreUpdateCurrentFieldMasterResult() = default;

        TSharedPtr<FPreUpdateCurrentFieldMasterResult> WithUploadToken(const TOptional<FString> UploadToken);
        TSharedPtr<FPreUpdateCurrentFieldMasterResult> WithUploadUrl(const TOptional<FString> UploadUrl);

        TOptional<FString> GetUploadToken() const;
        TOptional<FString> GetUploadUrl() const;

        static TSharedPtr<FPreUpdateCurrentFieldMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPreUpdateCurrentFieldMasterResult, ESPMode::ThreadSafe> FPreUpdateCurrentFieldMasterResultPtr;
}