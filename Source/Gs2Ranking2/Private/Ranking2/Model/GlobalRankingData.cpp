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

#include "Ranking2/Model/GlobalRankingData.h"

namespace Gs2::Ranking2::Model
{
    FGlobalRankingData::FGlobalRankingData():
        GlobalRankingDataIdValue(TOptional<FString>()),
        RankingNameValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        UserIdValue(TOptional<FString>()),
        IndexValue(TOptional<int32>()),
        RankValue(TOptional<int32>()),
        ScoreValue(TOptional<int64>()),
        MetadataValue(TOptional<FString>()),
        InvertUpdatedAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FGlobalRankingData::FGlobalRankingData(
        const FGlobalRankingData& From
    ):
        GlobalRankingDataIdValue(From.GlobalRankingDataIdValue),
        RankingNameValue(From.RankingNameValue),
        SeasonValue(From.SeasonValue),
        UserIdValue(From.UserIdValue),
        IndexValue(From.IndexValue),
        RankValue(From.RankValue),
        ScoreValue(From.ScoreValue),
        MetadataValue(From.MetadataValue),
        InvertUpdatedAtValue(From.InvertUpdatedAtValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithGlobalRankingDataId(
        const TOptional<FString> GlobalRankingDataId
    )
    {
        this->GlobalRankingDataIdValue = GlobalRankingDataId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithRank(
        const TOptional<int32> Rank
    )
    {
        this->RankValue = Rank;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithInvertUpdatedAt(
        const TOptional<int64> InvertUpdatedAt
    )
    {
        this->InvertUpdatedAtValue = InvertUpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FGlobalRankingData::GetGlobalRankingDataId() const
    {
        return GlobalRankingDataIdValue;
    }
    TOptional<FString> FGlobalRankingData::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<int64> FGlobalRankingData::GetSeason() const
    {
        return SeasonValue;
    }

    FString FGlobalRankingData::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FGlobalRankingData::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FGlobalRankingData::GetIndex() const
    {
        return IndexValue;
    }

    FString FGlobalRankingData::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IndexValue.GetValue());
    }
    TOptional<int32> FGlobalRankingData::GetRank() const
    {
        return RankValue;
    }

    FString FGlobalRankingData::GetRankString() const
    {
        if (!RankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RankValue.GetValue());
    }
    TOptional<int64> FGlobalRankingData::GetScore() const
    {
        return ScoreValue;
    }

    FString FGlobalRankingData::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FGlobalRankingData::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FGlobalRankingData::GetInvertUpdatedAt() const
    {
        return InvertUpdatedAtValue;
    }

    FString FGlobalRankingData::GetInvertUpdatedAtString() const
    {
        if (!InvertUpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), InvertUpdatedAtValue.GetValue());
    }
    TOptional<int64> FGlobalRankingData::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FGlobalRankingData::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FGlobalRankingData::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FGlobalRankingData::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FGlobalRankingData::GetRevision() const
    {
        return RevisionValue;
    }

    FString FGlobalRankingData::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FGlobalRankingData::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+):ranking:global:(?<season>.+):user:(?<scorerUserId>.+):score"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingData::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+):ranking:global:(?<season>.+):user:(?<scorerUserId>.+):score"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingData::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+):ranking:global:(?<season>.+):user:(?<scorerUserId>.+):score"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingData::GetRankingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+):ranking:global:(?<season>.+):user:(?<scorerUserId>.+):score"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingData::GetSeasonFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+):ranking:global:(?<season>.+):user:(?<scorerUserId>.+):score"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingData::GetScorerUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+):ranking:global:(?<season>.+):user:(?<scorerUserId>.+):score"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGlobalRankingData> FGlobalRankingData::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGlobalRankingData>()
            ->WithGlobalRankingDataId(Data->HasField(ANSI_TO_TCHAR("globalRankingDataId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("globalRankingDataId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRankingName(Data->HasField(ANSI_TO_TCHAR("rankingName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rankingName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSeason(Data->HasField(ANSI_TO_TCHAR("season")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("season"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIndex(Data->HasField(ANSI_TO_TCHAR("index")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("index"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRank(Data->HasField(ANSI_TO_TCHAR("rank")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("rank"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithScore(Data->HasField(ANSI_TO_TCHAR("score")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("score"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithInvertUpdatedAt(Data->HasField(ANSI_TO_TCHAR("invertUpdatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("invertUpdatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FGlobalRankingData::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GlobalRankingDataIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("globalRankingDataId"), GlobalRankingDataIdValue.GetValue());
        }
        if (RankingNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("rankingName"), RankingNameValue.GetValue());
        }
        if (SeasonValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("season"), FString::Printf(TEXT("%lld"), SeasonValue.GetValue()));
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (IndexValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("index"), IndexValue.GetValue());
        }
        if (RankValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("rank"), RankValue.GetValue());
        }
        if (ScoreValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("score"), FString::Printf(TEXT("%lld"), ScoreValue.GetValue()));
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (InvertUpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("invertUpdatedAt"), FString::Printf(TEXT("%lld"), InvertUpdatedAtValue.GetValue()));
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("updatedAt"), FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FGlobalRankingData::TypeName = "GlobalRankingData";
}
#include "Ranking2/Model/Cache/GlobalRankingData.h"

namespace Gs2::Ranking2::Model::Cache
{
    FString FGlobalRankingDataCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int64> CacheOwnerArgumentSeason,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("ranking2:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + CacheOwnerArgumentRankingName.Get(FString()) + FString(":")
            + (CacheOwnerArgumentSeason.IsSet() ? FString::Printf(TEXT("%lld"), CacheOwnerArgumentSeason.Get(0)) : FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":GlobalRankingData");
    }

    FString FGlobalRankingDataCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentScorerUserId
    )
    {
        return
            FString()
            + CacheOwnerArgumentScorerUserId.Get(FString())
            ;
    }

    bool FGlobalRankingDataCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int64> CacheOwnerArgumentSeason,
        TOptional<FString> CacheOwnerArgumentScorerUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Ranking2::Model::FGlobalRankingDataPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Ranking2::Model::FGlobalRankingDataPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Ranking2::Model::FGlobalRankingData>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentRankingName,
                CacheOwnerArgumentSeason,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentScorerUserId
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FGlobalRankingDataCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int64> CacheOwnerArgumentSeason,
        TOptional<FString> CacheOwnerArgumentScorerUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Ranking2::Model::FGlobalRankingDataPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentRankingName,
            CacheOwnerArgumentSeason,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentScorerUserId
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Ranking2::Model::FGlobalRankingDataPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Ranking2::Model::FGlobalRankingData>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Ranking2::Model::FGlobalRankingData::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FGlobalRankingDataCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Ranking2::Model::FGlobalRankingDataPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            Item->GetRankingName(),
            Item->GetSeason(),
            Item->GetUserId(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            Item->GetRankingName(),
            Item->GetSeason(),
            TimeOffset
        );
    }

    void FGlobalRankingDataCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int64> CacheOwnerArgumentSeason,
        TOptional<FString> CacheOwnerArgumentScorerUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Ranking2::Model::FGlobalRankingData::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentRankingName,
            CacheOwnerArgumentSeason,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentScorerUserId
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingDataCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int64> CacheOwnerArgumentSeason,
        TOptional<FString> CacheOwnerArgumentScorerUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Ranking2::Model::FGlobalRankingDataPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Ranking2::Model::FGlobalRankingDataPtr* CacheOwnerArgumentOutItem
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
        Gs2::Ranking2::Model::FGlobalRankingDataPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentRankingName,
                CacheOwnerArgumentSeason,
                CacheOwnerArgumentScorerUserId,
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
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentRankingName,
            CacheOwnerArgumentSeason,
            CacheOwnerArgumentScorerUserId,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("globalRankingData"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingDataCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int64> CacheOwnerArgumentSeason,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Ranking2::Model::FGlobalRankingData::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentRankingName,
            CacheOwnerArgumentSeason,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Ranking2::Model::FGlobalRankingDataPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FGlobalRankingData>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FGlobalRankingDataCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int64> CacheOwnerArgumentSeason,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Ranking2::Model::FGlobalRankingData::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentRankingName,
            CacheOwnerArgumentSeason,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}