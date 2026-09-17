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

#include "Log/Model/LogEntry.h"

namespace Gs2::Log::Model
{
    FLogEntry::FLogEntry():
        TimestampValue(TOptional<int64>()),
        StatusValue(TOptional<FString>()),
        DurationValue(TOptional<int64>()),
        LineValue(TOptional<FString>()),
        LabelsValue(nullptr)
    {
    }

    FLogEntry::FLogEntry(
        const FLogEntry& From
    ):
        TimestampValue(From.TimestampValue),
        StatusValue(From.StatusValue),
        DurationValue(From.DurationValue),
        LineValue(From.LineValue),
        LabelsValue(From.LabelsValue)
    {
    }

    TSharedPtr<FLogEntry> FLogEntry::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithDuration(
        const TOptional<int64> Duration
    )
    {
        this->DurationValue = Duration;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithLine(
        const TOptional<FString> Line
    )
    {
        this->LineValue = Line;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithLabels(
        const TSharedPtr<TArray<TSharedPtr<Model::FLabel>>> Labels
    )
    {
        this->LabelsValue = Labels;
        return SharedThis(this);
    }
    TOptional<int64> FLogEntry::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FLogEntry::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FLogEntry::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<int64> FLogEntry::GetDuration() const
    {
        return DurationValue;
    }

    FString FLogEntry::GetDurationString() const
    {
        if (!DurationValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DurationValue.GetValue());
    }
    TOptional<FString> FLogEntry::GetLine() const
    {
        return LineValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FLabel>>> FLogEntry::GetLabels() const
    {
        return LabelsValue;
    }

    TSharedPtr<FLogEntry> FLogEntry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLogEntry>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("status"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDuration(Data->HasField(ANSI_TO_TCHAR("duration")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("duration"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithLine(Data->HasField(ANSI_TO_TCHAR("line")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("line"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLabels(Data->HasField(ANSI_TO_TCHAR("labels")) ? [Data]() -> TSharedPtr<TArray<Model::FLabelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FLabelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("labels")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("labels")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("labels")))
                        {
                            v->Add(Model::FLabel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FLabelPtr>>());
    }

    TSharedPtr<FJsonObject> FLogEntry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("timestamp"), FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("status"), StatusValue.GetValue());
        }
        if (DurationValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("duration"), FString::Printf(TEXT("%lld"), DurationValue.GetValue()));
        }
        if (LineValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("line"), LineValue.GetValue());
        }
        if (LabelsValue != nullptr && LabelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *LabelsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("labels"), v);
        }
        return JsonRootObject;
    }

    FString FLogEntry::TypeName = "LogEntry";
}
#include "Log/Model/Cache/LogEntry.h"

namespace Gs2::Log::Model::Cache
{
    FString FLogEntryCache::CreateCacheParentKey(
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("log:")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":LogEntry");
    }

    FString FLogEntryCache::CreateCacheKey(
    )
    {
        return FString("Singleton");
    }

    bool FLogEntryCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Log::Model::FLogEntryPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Log::Model::FLogEntryPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Log::Model::FLogEntry>(
            CreateCacheParentKey(
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FLogEntryCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Log::Model::FLogEntryPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        CacheSnapshot->Put(Gs2::Log::Model::FLogEntry::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FLogEntryCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Log::Model::FLogEntry::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FLogEntryCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Log::Model::FLogEntryPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Log::Model::FLogEntryPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Log::Model::FLogEntryPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("logEntry"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FLogEntryCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Log::Model::FLogEntryPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Log::Model::FLogEntry::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Log::Model::FLogEntryPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Log::Model::FLogEntry>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FLogEntryCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Log::Model::FLogEntry::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}