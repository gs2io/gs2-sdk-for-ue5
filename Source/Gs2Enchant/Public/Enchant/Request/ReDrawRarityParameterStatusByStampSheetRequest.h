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

namespace Gs2::Enchant::Request
{
    class FReDrawRarityParameterStatusByStampSheetRequest;

    class GS2ENCHANT_API FReDrawRarityParameterStatusByStampSheetRequest final : public TSharedFromThis<FReDrawRarityParameterStatusByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FReDrawRarityParameterStatusByStampSheetRequest();
        FReDrawRarityParameterStatusByStampSheetRequest(
            const FReDrawRarityParameterStatusByStampSheetRequest& From
        );
        ~FReDrawRarityParameterStatusByStampSheetRequest() = default;

        TSharedPtr<FReDrawRarityParameterStatusByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReDrawRarityParameterStatusByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReDrawRarityParameterStatusByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FReDrawRarityParameterStatusByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReDrawRarityParameterStatusByStampSheetRequest, ESPMode::ThreadSafe> FReDrawRarityParameterStatusByStampSheetRequestPtr;
}