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

#pragma once

#include "CoreMinimal.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Model/Gs2GuildEzGuild.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Guild::Domain::Iterator
{

	class EZGS2_API FEzSearchGuildsIterator :
        public TSharedFromThis<FEzSearchGuildsIterator>
    {
        Gs2::Guild::Domain::Iterator::FSearchGuildsIteratorPtr It;
        Gs2::Guild::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        FString GuildModelName;
        TOptional<FString> DisplayName;
        TSharedPtr<TArray<int32>> Attributes1;
        TSharedPtr<TArray<int32>> Attributes2;
        TSharedPtr<TArray<int32>> Attributes3;
        TSharedPtr<TArray<int32>> Attributes4;
        TSharedPtr<TArray<int32>> Attributes5;
        TSharedPtr<TArray<FString>> JoinPolicies;
        TOptional<bool> IncludeFullMembersGuild;

	public:

        explicit FEzSearchGuildsIterator(
            Gs2::Guild::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            FString GuildModelName,
            TOptional<FString> DisplayName = TOptional<FString>(),
            TSharedPtr<TArray<int32>> Attributes1 = nullptr,
            TSharedPtr<TArray<int32>> Attributes2 = nullptr,
            TSharedPtr<TArray<int32>> Attributes3 = nullptr,
            TSharedPtr<TArray<int32>> Attributes4 = nullptr,
            TSharedPtr<TArray<int32>> Attributes5 = nullptr,
            TSharedPtr<TArray<FString>> JoinPolicies = nullptr,
            TOptional<bool> IncludeFullMembersGuild = TOptional<bool>()
        ) :
            It(
                Domain->SearchGuilds(
                    GuildModelName,
                    DisplayName,
                    Attributes1,
                    Attributes2,
                    Attributes3,
                    Attributes4,
                    Attributes5,
                    JoinPolicies,
                    IncludeFullMembersGuild
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection),
            GuildModelName(GuildModelName),
            DisplayName(DisplayName),
            Attributes1(Attributes1),
            Attributes2(Attributes2),
            Attributes3(Attributes3),
            Attributes4(Attributes4),
            Attributes5(Attributes5),
            JoinPolicies(JoinPolicies),
            IncludeFullMembersGuild(IncludeFullMembersGuild)
        {
        }

		FEzSearchGuildsIterator(
			const FEzSearchGuildsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection),
            GuildModelName(From.GuildModelName),
            DisplayName(From.DisplayName),
            Attributes1(From.Attributes1),
            Attributes2(From.Attributes2),
            Attributes3(From.Attributes3),
            Attributes4(From.Attributes4),
            Attributes5(From.Attributes5),
            JoinPolicies(From.JoinPolicies),
            IncludeFullMembersGuild(From.IncludeFullMembersGuild)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzSearchGuildsIterator;

			Gs2::Guild::Domain::Iterator::FSearchGuildsIterator::FIterator DomainIterator;
			Gs2::UE5::Guild::Model::FEzGuildPtr CurrentValue;
        	static Gs2::UE5::Guild::Model::FEzGuildPtr ConvertCurrent(
        		Gs2::Guild::Domain::Iterator::FSearchGuildsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Guild::Model::FEzGuild::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Guild::Domain::Iterator::FSearchGuildsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzSearchGuildsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
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

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Guild::Model::FEzGuildPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzSearchGuildsIterator> FEzSearchGuildsIteratorPtr;
}
