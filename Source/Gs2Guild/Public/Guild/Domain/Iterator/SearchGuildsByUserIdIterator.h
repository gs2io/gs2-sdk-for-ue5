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
 *
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Guild/Gs2Guild.h"

namespace Gs2::Guild::Domain::Iterator
{

    class GS2GUILD_API FSearchGuildsByUserIdIterator :
        public TSharedFromThis<FSearchGuildsByUserIdIterator>
    {
        const TSharedPtr<Core::Domain::FGs2> Gs2;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;
        const TOptional<FString> NamespaceName;
        const TOptional<FString> GuildModelName;
        const TOptional<FString> UserId;
        const TOptional<FString> DisplayName;
        const TSharedPtr<TArray<int32>> Attributes1;
        const TSharedPtr<TArray<int32>> Attributes2;
        const TSharedPtr<TArray<int32>> Attributes3;
        const TSharedPtr<TArray<int32>> Attributes4;
        const TSharedPtr<TArray<int32>> Attributes5;
        const TSharedPtr<TArray<FString>> JoinPolicies;
        const TOptional<bool> IncludeFullMembersGuild;
        const TOptional<FString> TimeOffsetToken;

    public:
        FSearchGuildsByUserIdIterator(
            const TSharedPtr<Core::Domain::FGs2> Gs2,
            const Gs2::Guild::FGs2GuildRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GuildModelName,
            const TOptional<FString> UserId,
            const TOptional<FString> DisplayName = TOptional<FString>(),
            const TSharedPtr<TArray<int32>> Attributes1 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes2 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes3 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes4 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes5 = nullptr,
            const TSharedPtr<TArray<FString>> JoinPolicies = nullptr,
            const TOptional<bool> IncludeFullMembersGuild = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );
        
        FSearchGuildsByUserIdIterator(
            const FSearchGuildsByUserIdIterator& From
        );

        class FIterator;

        class GS2GUILD_API FIteratorNextTask :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FGuild>
        {
        private:
            FIterator& Iterator;

        public:
            FIteratorNextTask(FIterator& Iterator) :
                Iterator(Iterator)
            {}

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result) override;

            static TSharedPtr<FAsyncTask<FIteratorNextTask>> Issue(FIterator& Iterator)
            {
                return Gs2::Core::Util::New<FAsyncTask<FIteratorNextTask>>(Iterator);
            }
        };

        class GS2GUILD_API FIterator
        {
            TSharedRef<FSearchGuildsByUserIdIterator> Self;
            TSharedPtr<TArray<Gs2::Guild::Model::FGuildPtr>> Range;
            TOptional<TArray<Gs2::Guild::Model::FGuildPtr>::TIterator> RangeIteratorOpt;
            Gs2::Core::Model::FGs2ErrorPtr ErrorValue;
            bool bLast;
            bool bEnd;
            TOptional<FString> PageToken;
            TOptional<int32> FetchSize;

            class FOneBeforeBegin {};
            class FEnd {};

            FIterator(
                const TSharedRef<FSearchGuildsByUserIdIterator> Iterable,
                FOneBeforeBegin
            );

            explicit FIterator(
                const TSharedRef<FSearchGuildsByUserIdIterator> Iterable
            ) :
                FIterator(Iterable, FOneBeforeBegin())
            {
                operator++();
            }

            FIterator(
                const TSharedRef<FSearchGuildsByUserIdIterator> Iterable,
                FEnd
            ) : Self(Iterable), bEnd(true)
            {}

        public:
            FIterator(
                const FIterator& Iterator
            ) :
                Self(Iterator.Self),
                Range(Iterator.Range),
                RangeIteratorOpt(Iterator.RangeIteratorOpt),
                ErrorValue(Iterator.ErrorValue),
                bLast(Iterator.bLast),
                bEnd(Iterator.bEnd),
                PageToken(Iterator.PageToken),
                FetchSize(Iterator.FetchSize)
            {}

            FIterator& operator*()
            {
                return *this;
            }

            const FIterator& operator*() const
            {
                return *this;
            }

            FIterator* operator->()
            {
                return this;
            }

            const FIterator* operator->() const
            {
                return this;
            }

            FIterator& operator++();

            friend bool operator== (const FIterator& a, const FIterator& b)
            {
                return a.Self == b.Self && a.bEnd && b.bEnd;
            }
            friend bool operator!= (const FIterator& a, const FIterator& b)
            {
                return !operator==(a, b);
            }

            bool HasNext() const
            {
                return !bEnd;
            }

            TSharedPtr<FAsyncTask<FIteratorNextTask>> Next()
            {
                return FIteratorNextTask::Issue(*this);
            }

            Gs2::Guild::Model::FGuildPtr& Current()
            {
                return **RangeIteratorOpt;
            }

            bool IsCurrentValid() const
            {
                return RangeIteratorOpt && *RangeIteratorOpt;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error() const
            {
                return ErrorValue;
            }

            bool IsError() const
            {
                return ErrorValue != nullptr;
            }

            void Retry()
            {
                if (ErrorValue && bLast)
                {
                    bLast = false;
                }
            }

            static FIterator OneBeforeBeginOf(const TSharedRef<FSearchGuildsByUserIdIterator> Iterable)
            {
                return FIterator(Iterable, FOneBeforeBegin());
            }

            static FIterator BeginOf(const TSharedRef<FSearchGuildsByUserIdIterator> Iterable)
            {
                return FIterator(Iterable);
            }

            static FIterator EndOf(const TSharedRef<FSearchGuildsByUserIdIterator> Iterable)
            {
                return FIterator(Iterable, FEnd());
            }
        };

        FIterator OneBeforeBegin();
        FIterator begin();
        FIterator end();
    };
    typedef TSharedPtr<FSearchGuildsByUserIdIterator> FSearchGuildsByUserIdIteratorPtr;
}
