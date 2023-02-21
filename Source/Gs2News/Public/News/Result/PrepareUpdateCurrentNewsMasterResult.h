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

namespace Gs2::News::Result
{
    class GS2NEWS_API FPrepareUpdateCurrentNewsMasterResult final : public TSharedFromThis<FPrepareUpdateCurrentNewsMasterResult>
    {
        TOptional<FString> UploadTokenValue;
        TOptional<FString> TemplateUploadUrlValue;
        
    public:
        
        FPrepareUpdateCurrentNewsMasterResult();
        FPrepareUpdateCurrentNewsMasterResult(
            const FPrepareUpdateCurrentNewsMasterResult& From
        );
        ~FPrepareUpdateCurrentNewsMasterResult() = default;

        TSharedPtr<FPrepareUpdateCurrentNewsMasterResult> WithUploadToken(const TOptional<FString> UploadToken);
        TSharedPtr<FPrepareUpdateCurrentNewsMasterResult> WithTemplateUploadUrl(const TOptional<FString> TemplateUploadUrl);

        TOptional<FString> GetUploadToken() const;
        TOptional<FString> GetTemplateUploadUrl() const;

        static TSharedPtr<FPrepareUpdateCurrentNewsMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareUpdateCurrentNewsMasterResult, ESPMode::ThreadSafe> FPrepareUpdateCurrentNewsMasterResultPtr;
}