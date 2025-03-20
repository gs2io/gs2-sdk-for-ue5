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
#include "Core/Gs2Object.h"

namespace Gs2::Script::Model
{
    class GS2SCRIPT_API FRandomUsed final : public FGs2Object, public TSharedFromThis<FRandomUsed>
    {
        TOptional<int64> CategoryValue;
        TOptional<int64> UsedValue;

    public:
        FRandomUsed();
        FRandomUsed(
            const FRandomUsed& From
        );
        virtual ~FRandomUsed() override = default;

        TSharedPtr<FRandomUsed> WithCategory(const TOptional<int64> Category);
        TSharedPtr<FRandomUsed> WithUsed(const TOptional<int64> Used);

        TOptional<int64> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<int64> GetUsed() const;
        FString GetUsedString() const;


        static TSharedPtr<FRandomUsed> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRandomUsed, ESPMode::ThreadSafe> FRandomUsedPtr;
}