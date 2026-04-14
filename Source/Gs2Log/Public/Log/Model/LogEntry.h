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
#include "Label.h"

namespace Gs2::Log::Model
{
    class GS2LOG_API FLogEntry final : public FGs2Object, public TSharedFromThis<FLogEntry>
    {
        TOptional<int64> TimestampValue;
        TOptional<FString> StatusValue;
        TOptional<int64> DurationValue;
        TOptional<FString> LineValue;
        TSharedPtr<TArray<TSharedPtr<FLabel>>> LabelsValue;

    public:
        FLogEntry();
        FLogEntry(
            const FLogEntry& From
        );
        virtual ~FLogEntry() override = default;

        TSharedPtr<FLogEntry> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FLogEntry> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FLogEntry> WithDuration(const TOptional<int64> Duration);
        TSharedPtr<FLogEntry> WithLine(const TOptional<FString> Line);
        TSharedPtr<FLogEntry> WithLabels(const TSharedPtr<TArray<TSharedPtr<FLabel>>> Labels);

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetStatus() const;
        TOptional<int64> GetDuration() const;
        FString GetDurationString() const;
        TOptional<FString> GetLine() const;
        TSharedPtr<TArray<TSharedPtr<FLabel>>> GetLabels() const;


        static TSharedPtr<FLogEntry> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLogEntry, ESPMode::ThreadSafe> FLogEntryPtr;
}